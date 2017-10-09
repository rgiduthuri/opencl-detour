# Source: https://github.com/rgiduthuri/opencl-detour
# Author: Radhakrishna Giduthuri
# Date: Aug 26, 2017

import os
import sys

# show usage
def showUsage():
    print('Usage: python ' + sys.argv[0] + ' [options] opencl-trace.log')
    print('        --output-dir <folder>     - specify output folder (default: current)')
    print('        --job-name <name>         - specify job name (default: detoured)')
    print('        --use-built-binary <0|1>  - specify whether to use built binary from source (default: 1)')
    print('        --remove-dup-code <0|1>   - specify whether to remove duplicate code (default: 0)')
    print('        --debug-flags <flags>     - specify debug flags (default: 0)')
    print('        --skip-till-token <token> - specify log till token (default: None)')

# process command-line arguments
outputFolder = '.'
jobName = 'detoured'
skipTillToken = ''
debugFlags = 0
useBuildBinary = 1
removeDuplicateCode = 1
pos = 1
while len(sys.argv) > (pos+1):
    if sys.argv[pos] == '--output-dir':
        outputFolder = sys.argv[pos+1]
    elif sys.argv[pos] == '--job-name':
        jobName = sys.argv[pos+1]
    elif sys.argv[pos] == '--use-built-binary':
        useBuildBinary = int(sys.argv[pos+1])
    elif sys.argv[pos] == '--remove-dup-code':
        removeDuplicateCode = int(sys.argv[pos+1])
    elif sys.argv[pos] == '--skip-till-token':
        skipTillToken = sys.argv[pos+1]
    elif sys.argv[pos] == '--debug-flags':
        debugFlags = int(sys.argv[pos+1])
    else:
        print('ERROR: invalid option: ' + sys.argv[pos])
        sys.exit(1)
    pos = pos + 2
if len(sys.argv) <= pos:
    showUsage()
    sys.exit(1)
inputLogFile = sys.argv[pos]
handleType = 'Handle_' + jobName

# create output files
print('OK: creating ' + outputFolder + '/' + jobName + '_job.h')
print('OK: creating ' + outputFolder + '/' + jobName + '_job.cpp')
print('OK: creating ' + outputFolder + '/' + jobName + '_main.cpp')
print('OK: creating ' + outputFolder + '/CMakeLists.txt')
if outputFolder != '.':
    os.system('mkdir -p ' + outputFolder)
fpH = open(outputFolder + '/' + jobName + '_job.h', 'w')
fpC = open(outputFolder + '/' + jobName + '_job.cpp', 'w')
fpM = open(outputFolder + '/' + jobName + '_main.cpp', 'w')
fpB = open(outputFolder + '/CMakeLists.txt', 'w')

# job data
#   dictProgram[programHandle] = ('source', options, [build-dev-list], [], <string>) or ('binary', options, [build-dev-list], [dev-list], [init-values])
#   dictBuffer[bufferHandle] = (flags, size, [init-values])
#   dictKernel[kernelHandle] = (name, programHandle, [(index,'buf'|'data',bufferHandle|[init-values]), ...])
#   dictDevice[devHandle] = cmdq
#   dictName[handle] = name
#   dictBufferUse[bufferHandle] = [kerneHandle-list]
#   dictKernelNameCount[kernelHandle] = count
dictProgram = {}
dictBuffer = {}
dictKernel = {}
dictDevice = {}
dictName = {}
dictBufferUse = {}
dictKernelNameCount = {}
listBuffer = []
listKernel = []
listProgram = []
listGraph = []
listGraphSaved = []

# utility functions
def GetParamList(line):
    return line.replace(' => ', ',').replace('(', ',').replace(')', '').replace(' ', '').split(',')

def GetParamList2(line):
    return line.replace(' => ', ',').replace('(', ',').replace(')', '').replace(' ', '').replace('{', '').replace('}', '').split(',')

def GenerateName(prefix):
    GenerateName.count += 1
    return prefix + '%05d' % (GenerateName.count - 1)
GenerateName.count = 0

# parse the log file
enableNDRange = True
if skipTillToken != '':
    enableNDRange = False
lineno = 0
for line in open(inputLogFile, 'r'):
    line = line.strip()
    lineno = lineno + 1
    line = line.replace('(nil)', '0x0')
    if (skipTillToken != '') and ('OPENCL-TRACE: ' + skipTillToken in line):
        enableNDRange = True
    elif 'OPENCL-TRACE: clCreateCommandQueue' in line:
        param = GetParamList(line)
        device = param[2]
        cmdq = param[5]
        dictDevice[device] = cmdq
    elif 'OPENCL-TRACE: clCreateProgramWithSource(' in line:
        param = GetParamList(line)
        prog = param[6]
        dictProgram[prog] = ['source', '', [], [], '']
        listProgram.append(prog)
    elif 'OPENCL-TRACE: PROGRAM-SOURCE' in line:
        prog = line.split(' ')[2]
        code = line[line.index('"')+1:-1]
        dictProgram[prog][4] = dictProgram[prog][4] + code
    elif 'OPENCL-TRACE: clCreateProgramWithBinary(' in line:
        param = GetParamList(line)
        prog = param[8]
        dictProgram[prog] = ['binary', '', [], [], []]
        listProgram.append(prog)
    elif 'OPENCL-TRACE: PROGRAM-BINARY' in line:
        params = line.split(' ')
        prog = params[2]
        device = params[3]
        dictProgram[prog][3].append(device)
        dictProgram[prog][4].append(params[4:])
    elif 'OPENCL-TRACE: PROGRAM-BUILD-BINARY' in line:
        if useBuildBinary:
            params = line.split(' ')
            prog = params[2]
            device = params[3]
            dictProgram[prog] = ['binary', '', [device], [device], [params[4:]]]
    elif 'OPENCL-TRACE: clBuildProgram(' in line:
        param = GetParamList(line)
        prog = param[1]
        dictProgram[prog][1] = line.split("'")[1]
    elif 'OPENCL-TRACE: PROGRAM-BUILD' in line:
        params = line.split(' ')
        prog = params[2]
        dictProgram[prog][2] = params[3:]
    elif 'OPENCL-TRACE: clCreateBuffer(' in line:
        param = GetParamList(line)
        flags = int(param[2])
        size = int(param[3])
        buff = param[6]
        dictBuffer[buff] = (flags, size, [])
        dictBufferUse[buff] = []
        listBuffer.append(buff)
    elif 'OPENCL-TRACE: BUFFER-WRITE' in line:
        params = line.split(' ')
        cmdq = params[2]
        buff = params[3]
        offset = int(params[4])
        size = int(params[5])
        if offset == 0:
            v = dictBuffer[buff]
            dictBuffer[buff] = (v[0], v[1], params[6:])
    elif 'OPENCL-TRACE: clCreateKernel(' in line:
        param = GetParamList(line)
        prog = param[1]
        name = param[2][1:-1]
        kern = param[4]
        dictKernel[kern] = (name, prog, [])
        listKernel.append(kern)
        if kern in dictKernelNameCount:
            dictKernelNameCount[kern] = dictKernelNameCount[kern] + 1
        else:
            dictKernelNameCount[kern] = 1
    elif 'OPENCL-TRACE: clReleaseKernel(' in line:
        param = GetParamList(line)
        kern = param[1]
        kernNew = kern + 'K' + str(dictKernelNameCount[kern])
        dictKernel[kernNew] = dictKernel[kern]
        for ie in range(len(listGraph)):
            if listGraph[ie][0] == dictKernel[kern]:
              listGraph[ie] = [dictKernel[kernNew], listGraph[ie][1]]
        listKernel.append(kernNew)
        del dictKernel[kern]
        listKernel.remove(kern)
    elif 'OPENCL-TRACE: KERNARG ' in line:
        param = line.split(' ')
        kern = param[2]
        arg  = int(param[3])
        size = int(param[4])
        if size == 8:
            if param[5] in dictBuffer:
                buff = param[5]
                v = (arg, 'buf', buff)
                if not kern in dictBufferUse[buff]:
                    dictBufferUse[buff].append(kern)
            else:
                v = (arg, 'data', [ int(param[5], 0) & 0xffffffff, int(param[5], 0) >> 32])
        else:
            v = []
            for i in param[5:]:
                v.append(int(i, 0))
            v = (arg, 'data', v)
        kv = dictKernel[kern]
        vv = kv[2]
        for i, iv in enumerate(vv):
            if vv[i][0] == arg:
                del vv[i]
                break
        vv.append(v)
        dictKernel[kern] = (kv[0], kv[1], vv)
    elif 'OPENCL-TRACE: clEnqueueNDRangeKernel(' in line:
        param = GetParamList2(line)
        cmdq = param[1]
        kern = param[2]
        dims = int(param[3])
        origin = []
        globalWork = []
        localWork = []
        for dim in range(dims):
            origin.append(int(param[4 + dim + dims * 0]))
            globalWork.append(int(param[4 + dim + dims * 1]))
            localWork.append(int(param[4 + dim + dims * 2]))
        enqueue = [dictKernel[kern], (dims, origin, globalWork, localWork)]
        listGraph.append(enqueue)
    elif 'OPENCL-TRACE: clEnqueueCopyBuffer(' in line:
        param = GetParamList2(line)
        cmdq = param[1]
        buf1 = param[2]
        buf2 = param[3]
        soffset = int(param[4])
        doffset = int(param[5])
        bufsize = int(param[6])
        enqueue = (('copy-buffer', buf1, buf2, soffset, doffset, bufsize))
        listGraph.append(enqueue)
    elif 'OPENCL-TRACE: clFinish(' in line:
        if len(listGraph) > 0:
            listGraphSaved = listGraph
            listGraph = []

# get saved graph and number of kernel count
listGraph = listGraphSaved
numKern = 0
numCopy = 0
for vk in listGraph:
    if len(vk) == 2:
        numKern = numKern + 1
    elif vk[0][0] == 'copy-buffer':
        numCopy = numCopy + 1

# get details of last job executed
listGraphPrograms = []
listGraphBuffers = []
for vk in listGraph:
    if len(vk) == 2:
        if not vk[0][1] in listGraphPrograms:
            listGraphPrograms.append(vk[0][1])
        for i in vk[0][2]:
            if (i[1] == 'buf') and (not i[2] in listGraphBuffers):
                listGraphBuffers.append(i[2])
    elif vk[0][0] == 'copy-buffer':
        if not vk[0][1] in listGraphBuffers:
            listGraphBuffers.append(vk[0][1])
        if not vk[0][2] in listGraphBuffers:
            listGraphBuffers.append(vk[0][2])

# identify re-usable program code
listProgSrcCode = []
dictProgSrcIndex = {}
listProgOptCode = []
dictProgOptIndex = {}
listProgBinCode = []
dictProgBinIndex = {}
for i, prog in enumerate(listGraphPrograms):
    v = dictProgram[prog]
    if v[0] == 'source':
        index = -1
        if removeDuplicateCode:
            for it, vt in enumerate(listProgSrcCode):
                if vt[1] == v[4]:
                    index = vt[0]
                    break
        if index < 0:
            index = i
            if removeDuplicateCode:
                listProgSrcCode.append((index, v[4]))
        dictProgSrcIndex[i] = index
        index = -1
        if removeDuplicateCode:
            for it, vt in enumerate(listProgOptCode):
                if vt[1] == v[1]:
                    index = vt[0]
                    break
        if index < 0:
            index = i
            if removeDuplicateCode:
                listProgOptCode.append((index, v[1]))
        dictProgOptIndex[i] = index
    else:
        index = -1
        if removeDuplicateCode:
            for it, vt in enumerate(listProgBinCode):
                if vt[1] == v[4][0]:
                    index = vt[0]
                    break
        if index < 0:
            index = i
            if removeDuplicateCode:
                listProgBinCode.append((index, v[4][0]))
        dictProgBinIndex[i] = index

# generate .h file
fpH.write('#ifndef __' + jobName + '_job_h__\n')
fpH.write('#define __' + jobName + '_job_h__\n')
fpH.write('#if defined(__APPLE__)\n')
fpH.write('#include <opencl.h>\n')
fpH.write('#else\n')
fpH.write('#include <CL/cl.h>\n')
fpH.write('#endif\n')
fpH.write('\n')
fpH.write('typedef struct __' + handleType + ' * ' + handleType + ';\n')
fpH.write('\n')
fpH.write('size_t ' + jobName + 'GetNumBuffer();\n')
fpH.write(handleType + ' ' + jobName + 'Create(cl_command_queue cmdq);\n')
fpH.write('int ' + jobName + 'Destroy(' + handleType + ' * pGraph);\n')
fpH.write('cl_mem ' + jobName + 'GetMem(' + handleType + ' job, size_t index);\n')
fpH.write('int ' + jobName + 'Run(' + handleType + ' job); // returns 0 on success, or ((errcode << 16) | call-index)\n')
fpH.write('\n')
fpH.write('#endif\n')

# generate .cpp file
fpC.write('#include "' + jobName + '_job.h"\n')
fpC.write('#ifndef NDEBUG\n')
fpC.write('#include <stdio.h>\n')
fpC.write('#endif\n')
if (debugFlags & 1):
    fpC.write('#include <string.h>\n')
fpC.write('\n')
fpC.write('struct __' + handleType + ' {\n')
fpC.write('    cl_context ctx;\n')
fpC.write('    cl_command_queue cmdq;\n')
fpC.write('    cl_mem buf[' + str(len(listGraphBuffers)) + '];\n')
fpC.write('    cl_kernel kern[' + str(numKern) + '];\n')
fpC.write('};\n')
fpC.write('\n')
fpC.write('#define ERRCHK_ERNUL(call) if((err = (call)) != CL_SUCCESS) return error_rnul(job, err, __LINE__)\n')
fpC.write('#define ERRCHK_NRNUL(call) if((call) == NULL) return error_rnul(job, err, __LINE__)\n')
fpC.write('#define ERRCHK_ERSET(call) err = error_rerr((call), err, __LINE__)\n')
fpC.write('#define ERRCHK_ERERR(call) if((err = (call)) != CL_SUCCESS) return error_rerr(err, 0, __LINE__)\n')
fpC.write('#ifndef NDEBUG\n')
fpC.write('#define ERRCHK_ERERR_RT(call,index) ERRCHK_ERERR(call)\n')
fpC.write('#else\n')
fpC.write('#define ERRCHK_ERERR_RT(call,index) if((err = (call)) != CL_SUCCESS) return (err << 16) | index;\n')
fpC.write('#endif\n')
fpC.write('static void error_msg(int err, int line)\n')
fpC.write('{\n')
fpC.write('#ifndef NDEBUG\n')
fpC.write('    printf("ERROR: detected err=%d at %s#%d\\n", err, __FILE__, line);\n')
fpC.write('#endif\n')
fpC.write('}\n')
fpC.write('static ' + handleType + ' error_rnul(' + handleType + ' job, int err, int line)\n')
fpC.write('{\n')
fpC.write('    error_msg(err, line);\n')
fpC.write('    ' + jobName + 'Destroy(&job);\n')
fpC.write('    return NULL;\n')
fpC.write('}\n')
fpC.write('static cl_int error_rerr(int e, int err, int line)\n')
fpC.write('{\n')
fpC.write('    if(e) error_msg(e, line);\n')
fpC.write('    return e ? e : err;\n')
fpC.write('}\n')
if (debugFlags & 1):
    fpC.write('static void dumpBuildInfo(cl_program program, cl_device_id device_id)\n')
    fpC.write('{\n')
    fpC.write('    size_t logSize = 1024 * 1024; char * log = new char[logSize]; memset(log, 0, logSize);\n')
    fpC.write('    clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, logSize, log, NULL);\n')
    fpC.write('    printf("<<<<\\n%s\\n>>>>\\n", log);\n')
    fpC.write('    delete[] log;\n')
    fpC.write('}\n')
fpC.write('\n')
for i, prog in enumerate(listGraphPrograms):
    v = dictProgram[prog]
    if v[0] == 'source':
        if dictProgSrcIndex[i] == i:
            fpC.write('extern const char s_program_src_%s_%d[];\n' % (jobName, i))
        if dictProgOptIndex[i] == i:
            fpC.write('extern const char s_program_options_%s_%d[];\n' % (jobName, i))
    else:
        if dictProgBinIndex[i] == i:
            fpC.write('extern const cl_uint s_program_bin_%s_%d[];\n' % (jobName, i))
            fpC.write('extern const size_t s_program_size_%s_%d;\n' % (jobName, i))
for i, buff in enumerate(listGraphBuffers):
    v = dictBuffer[buff]
    if len(v[2]) > 0:
        fpC.write('extern cl_uint s_buffer_bin_%s_%d[];\n' % (jobName, i))
fpC.write('\n')
fpC.write('size_t ' + jobName + 'GetNumBuffer()\n')
fpC.write('{\n')
fpC.write('    return ' + str(len(listGraphBuffers)) + ';\n')
fpC.write('}\n')
fpC.write('\n')
fpC.write(handleType + ' ' + jobName + 'Create(cl_command_queue cmdq)\n')
fpC.write('{\n')
fpC.write('    cl_int err;\n')
fpC.write('    ' + handleType + ' job = new __' + handleType + '();\n')
fpC.write('    if(job == NULL) return NULL;\n')
fpC.write('\n')
fpC.write('    job->cmdq = cmdq;\n')
fpC.write('    ERRCHK_ERNUL(clGetCommandQueueInfo(cmdq, CL_QUEUE_CONTEXT, sizeof(cl_context), &job->ctx, NULL));\n')
fpC.write('\n')
fpC.write('    cl_device_id device_id = NULL;\n')
fpC.write('    ERRCHK_ERNUL(clGetCommandQueueInfo(cmdq, CL_QUEUE_DEVICE, sizeof(cl_device_id), &device_id, NULL));\n')
fpC.write('\n')
fpC.write('    cl_program program;\n')
for i, prog in enumerate(listGraphPrograms):
    v = dictProgram[prog]
    if v[0] == 'source':
        options = 's_program_options_%s_%d' % (jobName, dictProgOptIndex[i])
        fpC.write('    const char * program_src_%d[] = { s_program_src_%s_%d };\n' % (i, jobName, dictProgSrcIndex[i]))
        fpC.write('    ERRCHK_NRNUL(program = clCreateProgramWithSource(job->ctx, 1, program_src_%d, NULL, &err));\n' % (i))
    else:
        options = '""'
        fpC.write('    const unsigned char * program_bin_%d[] = { (const unsigned char *) s_program_bin_%s_%d };\n' % (i, jobName, dictProgBinIndex[i]))
        fpC.write('    ERRCHK_NRNUL(program = clCreateProgramWithBinary(job->ctx, 1, &device_id, &s_program_size_%s_%d, program_bin_%d, NULL, &err));\n' % (jobName, dictProgBinIndex[i], i))
    if (debugFlags & 1):
        fpC.write('    err = clBuildProgram(program, 1, &device_id, %s, NULL, NULL);\n' % (options))
        fpC.write('    if(err) dumpBuildInfo(program, device_id);\n')
        fpC.write('    ERRCHK_ERNUL(err);\n')
    else:
        fpC.write('    ERRCHK_ERNUL(clBuildProgram(program, 1, &device_id, %s, NULL, NULL));\n' % (options))
    ik = 0
    for vk in listGraph:
        if len(vk) == 2:
            if prog == vk[0][1]:
                fpC.write('    ERRCHK_NRNUL(job->kern[%d] = clCreateKernel(program, "%s", &err));\n' % (ik, vk[0][0]))
            ik = ik + 1
    fpC.write('    ERRCHK_ERNUL(clReleaseProgram(program));\n')
fpC.write('\n')
for i, buff in enumerate(listGraphBuffers):
    v = dictBuffer[buff]
    flags = 'UNSUPPORTED_' + str(v[0])
    if v[0] == 1:
        flags = 'CL_MEM_READ_WRITE'
    elif v[0] == 2:
        flags = 'CL_MEM_WRITE_ONLY'
    elif v[0] == 4:
        flags = 'CL_MEM_READ_ONLY'
    fpC.write('    ERRCHK_NRNUL(job->buf[%d] = clCreateBuffer(job->ctx, %s, %d, NULL, &err));\n' % (i, flags, v[1]))
fpC.write('\n')
fpC.write('    cl_uint zero = 0;\n')
for i, buff in enumerate(listGraphBuffers):
    v = dictBuffer[buff]
    if len(v[2]) > 0:
        fpC.write('    ERRCHK_ERNUL(clEnqueueWriteBuffer(cmdq, job->buf[%d], CL_FALSE, 0, %ld, s_buffer_bin_%s_%d, 0, NULL, NULL));\n' % (i, v[1], jobName, i))
    else:
        fpC.write('    ERRCHK_ERNUL(clEnqueueFillBuffer(cmdq, job->buf[%d], &zero, sizeof(zero), 0, %ld, 0, NULL, NULL));\n' % (i, v[1]))
fpC.write('    ERRCHK_ERNUL(clFinish(cmdq));\n')
fpC.write('\n')
ik = 0
for vk in listGraph:
    if len(vk) == 2:
        v = vk[0][2] # (name, programHandle, [(index,'buf'|'data',bufferHandle|<byte-array>), ...])
        for a in v:
            if a[1] == 'buf':
                fpC.write('    ERRCHK_ERNUL(clSetKernelArg(job->kern[%d], %d, sizeof(cl_mem), &job->buf[%d]));\n' % (ik, a[0], listGraphBuffers.index(a[2])))
            elif a[1] == 'data':
                fpC.write('    { cl_uint arg[] = {');
                for d in a[2]:
                    fpC.write(' 0x%08x,' % (d))
                fpC.write(' }; ERRCHK_ERNUL(clSetKernelArg(job->kern[%d], %d, sizeof(arg), arg)); }\n' % (ik, a[0]))
        ik = ik + 1
fpC.write('\n')
fpC.write('    return job;\n')
fpC.write('}\n')
fpC.write('\n')
fpC.write('int ' + jobName + 'Destroy(' + handleType + ' * pGraph)\n')
fpC.write('{\n')
fpC.write('    ' + handleType + ' job = *pGraph;\n')
fpC.write('    cl_int err = 0;\n')
fpC.write('\n')
for i in range(numKern):
    fpC.write('    if(job->kern[%d]) ERRCHK_ERSET(clReleaseKernel(job->kern[%d]));\n' % (i, i))
fpC.write('\n')
for i in range(len(listGraphBuffers)):
    fpC.write('    if(job->buf[%d]) ERRCHK_ERSET(clReleaseMemObject(job->buf[%d]));\n' % (i, i))
fpC.write('\n')
fpC.write('    delete job;\n')
fpC.write('    *pGraph = NULL;\n')
fpC.write('    return err;\n')
fpC.write('}\n')
fpC.write('\n')
fpC.write('cl_mem ' + jobName + 'GetMem(' + handleType + ' job, size_t index)\n')
fpC.write('{\n')
fpC.write('    return (index < %d) ? job->buf[index] : NULL;\n' % (len(listGraphBuffers)))
fpC.write('}\n')
fpC.write('\n')
fpC.write('int ' + jobName + 'Run(' + handleType + ' job)\n')
fpC.write('{\n')
fpC.write('    cl_int err;\n')
fpC.write('\n')
ik = 0
ic = 0
for vk in listGraph: # (kernelHandle, dims, origin, globalWork, localWork)
    if len(vk) == 2:
        dims = vk[1][0]
        origin = vk[1][1]
        globalWork = vk[1][2]
        localWork = vk[1][3]
        fpC.write('    {')
        fpC.write(' size_t globalWork[%d] = {' % (dims))
        for i in range(dims):
            fpC.write(' %d,' % (globalWork[i]))
        fpC.write(' };')
        if localWork[0] >= 0:
            fpC.write(' size_t localWork[%d] = {' % (dims))
            for i in range(dims):
                fpC.write(' %d,' % (localWork[i]))
            fpC.write(' };')
        if (dims == 3) and (origin[0] == 0) and (origin[1] == 0) and (origin[2] == 0):
            origin[0] = -1
            origin[1] = -1
            origin[2] = -1
        if origin[0] >= 0:
            fpC.write(' size_t origin[%d] = {' % (dims))
            for i in range(dims):
                fpC.write(' %d,' % (origin[i]))
            fpC.write(' };')
        fpC.write(' ERRCHK_ERERR_RT(clEnqueueNDRangeKernel(job->cmdq, job->kern[%d], %d,' % (ik, dims))
        if origin[0] >= 0:
            fpC.write(' origin,')
        else:
            fpC.write(' NULL,')
        fpC.write(' globalWork,')
        if localWork[0] >= 0:
            fpC.write(' localWork,')
        else:
            fpC.write(' NULL,')
        fpC.write(' 0, NULL, NULL), %d); }\n' % (ic))
        ik = ik + 1
    elif vk[0] == 'copy-buffer':
        buf1 = listGraphBuffers.index(vk[1])
        buf2 = listGraphBuffers.index(vk[2])
        soffset = vk[3]
        doffset = vk[4]
        bufsize = vk[5]
        fpC.write('    ERRCHK_ERERR_RT(clEnqueueCopyBuffer(job->cmdq, job->buf[%d], job->buf[%d], %d, %d, %d, 0, NULL, NULL), %d);\n' % (buf1, buf2, soffset, doffset, bufsize, ic))
    ic = ic + 1
fpC.write('\n')
fpC.write('    return 0;\n')
fpC.write('}\n')
fpC.write('\n')
numProgSrc = 0
numProgBin = 0
totalProgSrc = 0
totalProgBin = 0
for i, prog in enumerate(listGraphPrograms):
    v = dictProgram[prog]
    if v[0] == 'source':
        if dictProgSrcIndex[i] == i:
            fpC.write('const char s_program_src_%s_%d[] = "%s";\n' % (jobName, i, v[4]))
            totalProgSrc = totalProgSrc + len(v[4])
            numProgSrc = numProgSrc + 1
        if dictProgOptIndex[i] == i:
            fpC.write('const char s_program_options_%s_%d[] = "%s";\n' % (jobName, i, v[1]))
            totalProgSrc = totalProgSrc + len(v[1])
    else:
        if dictProgBinIndex[i] == i:
            if len(v[4]) != 1:
                print('ERROR: this implementation supports program binaries on one device only')
            fpC.write('const cl_uint s_program_bin_%s_%d[] = {' % (jobName, i))
            for j in v[4][0][1:]:
                fpC.write(' %s,' % (j))
            fpC.write(' };\n')
            fpC.write('const size_t s_program_size_%s_%d = %d;\n' % (jobName, i, int(v[4][0][0])))
            numProgBin = numProgBin + 1
            totalProgBin = totalProgBin + int(v[4][0][0])
totalBufferAlloc = 0
totalBufferInit = 0
for i, buff in enumerate(listGraphBuffers):
    v = dictBuffer[buff]
    if len(v[2]) > 2:
        fpC.write('cl_uint s_buffer_bin_%s_%d[] = {' % (jobName, i))
        for d in v[2]:
            fpC.write(' %s,' % (d))
        fpC.write(' };\n')
        totalBufferInit = totalBufferInit + v[1]
    totalBufferAlloc = totalBufferAlloc + v[1]
print('OK: job allocates %d buffers (%d bytes allocation with %d bytes pre-initialized)' % (len(listGraphBuffers), totalBufferAlloc, totalBufferInit))
print('OK: job uses %d kernels created from %d programs (unique %d source + %d binary) with %d bytes of code size' % (numKern, len(listGraphPrograms), numProgSrc, numProgBin, totalProgSrc + totalProgBin))
if numCopy > 0:
    print('OK: job uses %d buffer copies' % (numCopy))

# generate _main.cpp
fpM.write('#include "' + jobName + '_job.h"\n')
fpM.write('#include <stdio.h>\n')
fpM.write('#include <string.h>\n')
fpM.write('#include <chrono>\n')
fpM.write('\n')
fpM.write('#define ERRCHK_ERNUL(call) if((err = (call)) != CL_SUCCESS) return error_rnul(job, err, __LINE__)\n')
fpM.write('#define ERRCHK_NRNUL(call) if((call) == NULL) return error_rnul(job, err, __LINE__)\n')
fpM.write('#define ERRCHK_ERSET(call) err = error_rerr((call), err, __LINE__)\n')
fpM.write('#define ERRCHK_ERERR(call) if((err = (call)) != CL_SUCCESS) return error_rerr(err, 0, __LINE__)\n')
fpM.write('static void error_msg(int err, int line)\n')
fpM.write('{\n')
fpM.write('    printf("ERROR: detected err=%d at %s#%d\\n", err, __FILE__, line);\n')
fpM.write('}\n')
fpM.write('static ' + handleType + ' error_rnul(' + handleType + ' job, int err, int line)\n')
fpM.write('{\n')
fpM.write('    error_msg(err, line);\n')
fpM.write('    ' + jobName + 'Destroy(&job);\n')
fpM.write('    return NULL;\n')
fpM.write('}\n')
fpM.write('static cl_int error_rerr(int e, int err, int line)\n')
fpM.write('{\n')
fpM.write('    if(e) error_msg(e, line);\n')
fpM.write('    return e ? e : err;\n')
fpM.write('}\n')
fpM.write('\n')
fpM.write('int main(int argc, char * argv[])\n')
fpM.write('{\n')
fpM.write('    const char * usage = "Usage: job [[read:bufIndex,fileName]|[write:bufIndex,fileName]|[iter:numIter]]";\n')
fpM.write('    int err;\n')
fpM.write('\n')
fpM.write('    std::chrono::steady_clock::time_point begin, end; float time;\n')
fpM.write('    begin = std::chrono::steady_clock::now();\n')
fpM.write('    cl_platform_id platform_id;\n')
fpM.write('    ERRCHK_ERERR(clGetPlatformIDs(1, &platform_id, NULL));\n')
fpM.write('    cl_context_properties ctxprop[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platform_id, 0, 0 };\n')
fpM.write('    cl_context ctx = clCreateContextFromType(ctxprop, CL_DEVICE_TYPE_GPU, NULL, NULL, &err);\n')
fpM.write('    ERRCHK_ERERR(err);\n')
fpM.write('    cl_device_id device_list[16] = { 0 };\n')
fpM.write('    ERRCHK_ERERR(clGetContextInfo(ctx, CL_CONTEXT_DEVICES, sizeof(device_list), device_list, NULL));\n')
fpM.write('    cl_device_id device_id = device_list[0];\n')
fpM.write('#if defined(CL_VERSION_2_0)\n')
fpM.write('    cl_command_queue cmdq = clCreateCommandQueueWithProperties(ctx, device_id, NULL, &err);\n')
fpM.write('    ERRCHK_ERERR(err);\n')
fpM.write('#else\n')
fpM.write('    cl_command_queue cmdq = clCreateCommandQueue(ctx, device_id, 0, &err);\n')
fpM.write('    ERRCHK_ERERR(err);\n')
fpM.write('#endif\n')
fpM.write('    end = std::chrono::steady_clock::now();\n')
fpM.write('    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();\n')
fpM.write('    printf("OK: **** OpenCL context creation took %.2f milliseconds\\n", time);\n')
fpM.write('    fflush(stdout);\n')
fpM.write('\n')
fpM.write('    begin = std::chrono::steady_clock::now();\n')
fpM.write('    ' + handleType + ' job = ' + jobName + 'Create(cmdq);\n')
fpM.write('    if(!job) { printf("ERROR: ' + jobName + 'Create failed\\n"); return 1; }\n')
fpM.write('    end = std::chrono::steady_clock::now();\n')
fpM.write('    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();\n')
fpM.write('    printf("OK: **** ' + jobName + 'Create() [NumBuffer=%ld] took %.2f milliseconds\\n", ' + jobName + 'GetNumBuffer(), time);\n')
fpM.write('    fflush(stdout);\n')
fpM.write('\n')
fpM.write('    int numIter = 5;\n')
fpM.write('    const char * memDumpFolder = NULL;\n')
fpM.write('    for(int i = 1; i < argc; i++) {\n')
fpM.write('        if(!strncmp(argv[i], "read:", 5)) {\n')
fpM.write('            size_t index = 0;\n')
fpM.write('            char fileName[1024] = { 0 };\n')
fpM.write('            if(sscanf(&argv[i][5], "%ld,%s", &index, fileName) != 2) { printf("ERROR: invalid argument: %s\\n%s\\n", argv[i], usage); return -1; }\n')
fpM.write('            if(index >= ' + jobName + 'GetNumBuffer()) { printf("ERROR: invalid buffer index to read: %ld\\n", index); return -1; }\n')
fpM.write('            FILE * fp = fopen(fileName, "rb"); if(!fp) { printf("ERROR: unable to open: %s\\n", fileName); return -1; }\n')
fpM.write('            cl_mem mem = ' + jobName + 'GetMem(job, index);\n')
fpM.write('            size_t size = 0;\n')
fpM.write('            ERRCHK_ERERR(clGetMemObjectInfo(mem, CL_MEM_SIZE, sizeof(size), &size, NULL));\n')
fpM.write('            void * p = clEnqueueMapBuffer(cmdq, mem, CL_TRUE, CL_MAP_WRITE, 0, size, 0, NULL, NULL, &err);\n')
fpM.write('            ERRCHK_ERERR(err);\n')
fpM.write('            ERRCHK_ERERR(clFinish(cmdq));\n')
fpM.write('            if(fread(p, 1, size, fp) != size) { printf("ERROR: unable to read %ld bytes from %s\\n", size, fileName); return -1; }\n')
fpM.write('            ERRCHK_ERERR(clEnqueueUnmapMemObject(cmdq, mem, p, 0, NULL, NULL));\n');
fpM.write('            ERRCHK_ERERR(clFinish(cmdq));\n')
fpM.write('            fclose(fp);\n')
fpM.write('            printf("OK: read mem[%ld] from %s (%ld bytes)\\n", index, fileName, size);\n')
fpM.write('        }\n')
fpM.write('        else if(strncmp(argv[i], "iter:", 5) == 0) sscanf(&argv[i][5], "%d", &numIter);\n')
fpM.write('        else if(strncmp(argv[i], "dumpdir:", 8) == 0) memDumpFolder = &argv[i][8];\n')
fpM.write('        else if(strncmp(argv[i], "write:", 6) != 0) { printf("ERROR: invalid option: %s\\n%s\\n", argv[i], usage); return -1; }\n')
fpM.write('    }\n')
fpM.write('\n')
fpM.write('    begin = std::chrono::steady_clock::now();\n')
fpM.write('    ERRCHK_ERERR(' + jobName + 'Run(job));\n')
fpM.write('    ERRCHK_ERERR(clFinish(cmdq));\n')
fpM.write('    end = std::chrono::steady_clock::now();\n')
fpM.write('    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();\n')
fpM.write('    printf("OK: [%2d] ' + jobName + 'Run() took %.2f milliseconds\\n", 0, time);\n')
fpM.write('    fflush(stdout);\n')
fpM.write('\n')
fpM.write('    for(int i = 1; i < argc; i++) {\n')
fpM.write('        if(!strncmp(argv[i], "write:", 6)) {\n')
fpM.write('            size_t index = 0;\n')
fpM.write('            char fileName[1024] = { 0 };\n')
fpM.write('            if(sscanf(&argv[i][6], "%ld,%s", &index, fileName) != 2) { printf("ERROR: invalid argument: %s\\n%s\\n", argv[i], usage); return -1; }\n')
fpM.write('            if(index >= ' + jobName + 'GetNumBuffer()) { printf("ERROR: invalid buffer index to read: %ld\\n", index); return -1; }\n')
fpM.write('            FILE * fp = fopen(fileName, "wb"); if(!fp) { printf("ERROR: unable to create: %s\\n", fileName); return -1; }\n')
fpM.write('            cl_mem mem = ' + jobName + 'GetMem(job, index);\n')
fpM.write('            size_t size = 0;\n')
fpM.write('            ERRCHK_ERERR(clGetMemObjectInfo(mem, CL_MEM_SIZE, sizeof(size), &size, NULL));\n')
fpM.write('            void * p = clEnqueueMapBuffer(cmdq, mem, CL_TRUE, CL_MAP_READ, 0, size, 0, NULL, NULL, &err);\n')
fpM.write('            ERRCHK_ERERR(err);\n')
fpM.write('            ERRCHK_ERERR(clFinish(cmdq));\n')
fpM.write('            fwrite(p, 1, size, fp);\n')
fpM.write('            ERRCHK_ERERR(clEnqueueUnmapMemObject(cmdq, mem, p, 0, NULL, NULL));\n');
fpM.write('            ERRCHK_ERERR(clFinish(cmdq));\n')
fpM.write('            fclose(fp);\n')
fpM.write('            printf("OK: saved mem[%ld] into %s (%ld bytes)\\n", index, fileName, size);\n')
fpM.write('        }\n')
fpM.write('    }\n')
fpM.write('\n')
fpM.write('    if(memDumpFolder) {\n')
fpM.write('        for(size_t index = 0; index < ' + jobName + 'GetNumBuffer(); index++) {\n')
fpM.write('            char fileName[1024];\n')
fpM.write('            sprintf(fileName, "%s/zmem-%04ld.raw", memDumpFolder, index);\n')
fpM.write('            FILE * fp = fopen(fileName, "wb"); if(!fp) { printf("ERROR: unable to create: %s\\n", fileName); return -1; }\n')
fpM.write('            cl_mem mem = ' + jobName + 'GetMem(job, index);\n')
fpM.write('            size_t size = 0;\n')
fpM.write('            ERRCHK_ERERR(clGetMemObjectInfo(mem, CL_MEM_SIZE, sizeof(size), &size, NULL));\n')
fpM.write('            void * p = clEnqueueMapBuffer(cmdq, mem, CL_TRUE, CL_MAP_READ, 0, size, 0, NULL, NULL, &err);\n')
fpM.write('            ERRCHK_ERERR(err);\n')
fpM.write('            ERRCHK_ERERR(clFinish(cmdq));\n')
fpM.write('            fwrite(p, 1, size, fp);\n')
fpM.write('            ERRCHK_ERERR(clEnqueueUnmapMemObject(cmdq, mem, p, 0, NULL, NULL));\n');
fpM.write('            ERRCHK_ERERR(clFinish(cmdq));\n')
fpM.write('            fclose(fp);\n')
fpM.write('            printf("OK: saved mem[%ld] into %s (%ld bytes)\\n", index, fileName, size);\n')
fpM.write('        }\n')
fpM.write('    }\n')
fpM.write('\n')
fpM.write('    for(int iter = 1; iter <= numIter; iter++) {\n')
fpM.write('        begin = std::chrono::steady_clock::now();\n')
fpM.write('        ERRCHK_ERERR(' + jobName + 'Run(job));\n')
fpM.write('        ERRCHK_ERERR(clFinish(cmdq));\n')
fpM.write('        end = std::chrono::steady_clock::now();\n')
fpM.write('        time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();\n')
fpM.write('        printf("OK: [%2d] ' + jobName + 'Run() took %.2f milliseconds\\n", iter, time);\n')
fpM.write('        fflush(stdout);\n')
fpM.write('    }\n')
fpM.write('\n')
fpM.write('    begin = std::chrono::steady_clock::now();\n')
fpM.write('    ERRCHK_ERERR(' + jobName + 'Destroy(&job));\n')
fpM.write('    ERRCHK_ERERR(clReleaseCommandQueue(cmdq));\n')
fpM.write('    ERRCHK_ERERR(clReleaseContext(ctx));\n')
fpM.write('    end = std::chrono::steady_clock::now();\n')
fpM.write('    time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();\n')
fpM.write('    printf("OK: **** ' + jobName + 'Destroy() and OpenCL release took %.2f milliseconds\\n", time);\n')
fpM.write('    fflush(stdout);\n')
fpM.write('\n')
fpM.write('    return 0;\n')
fpM.write('}\n')

# generate CMakeLists.txt
fpB.write('cmake_minimum_required (VERSION 2.8)\n')
fpB.write('project (' + jobName + ')\n')
fpB.write('set (CMAKE_CXX_STANDARD 11)\n')
fpB.write('find_package(OpenCL REQUIRED)\n')
fpB.write('list(APPEND SOURCES ' + jobName + '_job.cpp ' + jobName + '_main.cpp)\n')
fpB.write('add_executable(' + jobName + ' ${SOURCES})\n')
fpB.write('include_directories(${OpenCL_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIRS}/Headers)\n')
fpB.write('target_link_libraries(' + jobName + ' ${OpenCL_LIBRARIES})\n')
fpB.write('if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")\n')
fpB.write('    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")\n')
fpB.write('    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")\n')
fpB.write('else()\n')
fpB.write('    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")\n')
fpB.write('endif()\n')

# close files
fpH.close()
fpC.close()
fpM.close()
fpB.close()

print('OK: good luck!')

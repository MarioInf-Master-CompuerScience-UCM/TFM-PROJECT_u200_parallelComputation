#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <mutex>
#include <omp.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <cstdint>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <xrt.h>
#include <xrt/xrt_device.h>
#include "studyCase3Host_c.hpp"


using namespace std;
using globalConfiguration_typeData::typeData;
using globalConfiguration_typeData::typeData_fixed;

using cl::Event;
using cl::CommandQueue;
using cl::Kernel;
using cl::Buffer;

atomic<bool> StudyCase3Host_c::stop_thread(false);
double StudyCase3Host_c::sharedVariable=0.0f;

//********************************
//* CONSTRUCTORS AND DESTRUCTORS *
//********************************
StudyCase3Host_c::StudyCase3Host_c(){}
StudyCase3Host_c::~StudyCase3Host_c(){}

//*************************************
// MAIN FUNCTION - START
//*************************************
bool StudyCase3Host_c::exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile){
    fileWriter_logFile.writeln("Executing host function \"VectorAddHost::StudyCase3Host_c_exec\". Execution configuration:\n" + exec.displayInfo("\t"));


    //STEP 0 - START: Initializating parameters"
    fileWriter_logFile.writeln("STEP 0 - START: Initializating parameters");
    
    unsigned int SIZE=0;    
    bool result = initParameter(exec, SIZE);
    if(!result){
        cout << "\033[1;31mERROR..:Entry params unexpected. Fanalizating execution.\033[0m\n"  << endl;
        return false;
    }
    StudyCase3Kernel data = StudyCase3Kernel(SIZE);
    EventTimer event;
    Event event_sp;
    double resultMeasure_Device=0.0f, resultMeasure_CPU=0.0f, resultMeasure_CPUopt=0.0f;
    vector<double> resultMeasure_CPUopt_byPack = vector<double>();


    fileWriter_logFile.writeln("STEP 0 - END: Initializating parameters");
    //STEP 0 - END: Initializating parameters"


    //STEP 1 - START: Initializaton OpenCL and load kernels"
    fileWriter_logFile.writeln("STEP 1 - START: Initializaton OpenCL and load kernels");
    event.add("Initializaton OpenCL and load kernels");

    xilinx::example_utils::XilinxOclHelper xocl;
    xocl.initialize(exec.get_kernelPackage());
    CommandQueue q = xocl.get_command_queue();
    Kernel ker = xocl.get_kernel(exec.get_kernel());

    event.finish();
    fileWriter_logFile.write("STEP 1 - END: Initializaton OpenCL and load kernels (" + event.getInfoEvents(0));
    //STEP 1 - END: Initializaton OpenCL and load kernels"


    //STEP 2 - START: Running kernel in CPU"
    fileWriter_logFile.writeln("STEP 2 - START: Running kernel in CPU");

    if(exec.get_measurePower_CPU()){
        resultMeasure_CPU = executeAndMeasure_CPU(data, event);    
    }else{
        data.kernel_studyCase3_c_CPU();
    }

    fileWriter_logFile.write("STEP 2 - END: Running kernel in CPU (" + event.getInfoEvents(1));
    //STEP 2 - END: Running kernel in CPU"


    //STEP 3 - START: Running kernel in CPU optimizated"
    fileWriter_logFile.writeln("STEP 3 - START: Running kernel in CPU optimizated");

    if(exec.get_measurePower_CPUopt()){
        resultMeasure_CPUopt = executeAndMeasure_CPUopt(data, resultMeasure_CPUopt_byPack, event);    
    }else{
        data.kernel_studyCase3_c_CPU_opt();
    }

    fileWriter_logFile.write("STEP 3 - END: Running kernel in CPU optimizated (" + event.getInfoEvents(2));
    //STEP 3 - END: Running kernel in CPU optimizated"

    
    //STEP 4 - START: Creating buffer 
    fileWriter_logFile.writeln("STEP 4 - START: Creating buffer");
    event.add("Creating buffers");

    cl_mem_ext_ptr_t bank_ext0;
    bank_ext0.flags = 0 | XCL_MEM_TOPOLOGY;
    bank_ext0.obj   = NULL;
    bank_ext0.param = 0;

    cl_mem_ext_ptr_t bank_ext1;
    bank_ext1.flags = 1 | XCL_MEM_TOPOLOGY;
    bank_ext1.obj   = NULL;
    bank_ext1.param = 0;

    cl_mem_ext_ptr_t bank_ext2;
    bank_ext2.flags = 2 | XCL_MEM_TOPOLOGY;
    bank_ext2.obj   = NULL;
    bank_ext2.param = 0;

    Buffer sendBuff_vA(xocl.get_context(),
                        static_cast<cl_mem_flags>(CL_MEM_READ_ONLY | CL_MEM_EXT_PTR_XILINX),
                        data.get_SIZE() * sizeof(typeData_fixed),
                        &bank_ext0,
                        NULL);

    Buffer sendBuff_vB(xocl.get_context(),
                        static_cast<cl_mem_flags>(CL_MEM_READ_ONLY | CL_MEM_EXT_PTR_XILINX),
                        data.get_SIZE() * sizeof(typeData_fixed),
                        &bank_ext1,
                        NULL);

    Buffer recvBuff_resultDevice(xocl.get_context(),
                        static_cast<cl_mem_flags>(CL_MEM_WRITE_ONLY | CL_MEM_EXT_PTR_XILINX),
                        data.get_SIZE() * sizeof(typeData_fixed),
                        &bank_ext2,
                        NULL);

    ker.setArg(0, sendBuff_vA);
    ker.setArg(1, sendBuff_vB);
    ker.setArg(2, recvBuff_resultDevice);

    typeData_fixed *temp_vA = (typeData_fixed *)q.enqueueMapBuffer(sendBuff_vA,
                                                        CL_TRUE,
                                                        CL_MAP_WRITE,
                                                        0,
                                                        data.get_SIZE() * sizeof(typeData_fixed));

    typeData_fixed *temp_vB = (typeData_fixed *)q.enqueueMapBuffer(sendBuff_vB,
                                                        CL_TRUE,
                                                        CL_MAP_WRITE,
                                                        0,
                                                        data.get_SIZE() * sizeof(typeData_fixed));

    typeData_fixed *temp_resultDevice = (typeData_fixed *)q.enqueueMapBuffer(recvBuff_resultDevice,
                                                        CL_TRUE,
                                                        CL_MAP_WRITE | CL_MAP_READ,
                                                        0,
                                                        data.get_SIZE() * sizeof(typeData_fixed));

    ensamble_dataToBuffers(data, temp_vA, temp_vB, temp_resultDevice);

    event.finish();
    fileWriter_logFile.write("STEP 4 - END: Creating buffer (" + event.getInfoEvents(3)); 
    //STEP 4 - END: Creating buffer 


    //STEP 5 - START: Transmision data to device
    fileWriter_logFile.writeln("STEP 5 - START: Transmision data to device");
    event.add("Transmision data to device");
    
    q.enqueueMigrateMemObjects({sendBuff_vA, sendBuff_vB}, 0, NULL, &event_sp);
    clWaitForEvents(1, (const cl_event *)&event_sp);

    event.finish();
    fileWriter_logFile.write("5 - END: Transmision data to device (" + event.getInfoEvents(4));
    //STEP 5 - END: Transmision data to device 


    //STEP 6 - START: Device execution
    fileWriter_logFile.writeln("STEP 6 - START: Device execution");
    
    if(exec.get_measurePower_device() && exec.get_kernelPackage().find("hw.xclbin") != string::npos){
        if(exec.get_kernelPackage().find("hw.xclbin") == string::npos){
            fileWriter_logFile.writeln("ERROR..: We can't measure power device in sw_emu or hw_emu.");
        }else{

            stop_thread.store(false);
            q.enqueueTask(ker, NULL, &event_sp);
            event.add("Device execution");

            thread thread_deviceMeasure(threadFunction_DevicePowerMeasure);
            
            clWaitForEvents(1, (const cl_event *)&event_sp);
            event.finish();

            stop_thread.store(true);
            if (thread_deviceMeasure.joinable()) {
                thread_deviceMeasure.join();
            }
            
            resultMeasure_Device = sharedVariable;
        }

    }else{
        q.enqueueTask(ker, NULL, &event_sp);
        event.add("Device execution");
        clWaitForEvents(1, (const cl_event *)&event_sp);  
        event.finish();      
    }

    fileWriter_logFile.write("STEP 6 - END: Device execution (" + event.getInfoEvents(5));
    //STEP 6 - END: Device execution


    //STEP 7 - START: Transmision data from device
    fileWriter_logFile.writeln("STEP 7 - START: Transmision data from device");
    event.add("Transmision data from device ");

    q.enqueueMigrateMemObjects({recvBuff_resultDevice}, CL_MIGRATE_MEM_OBJECT_HOST, NULL, &event_sp);
    clWaitForEvents(1, (const cl_event *)&event_sp);
    q.finish();

    event.finish();
    fileWriter_logFile.write("STEP 7 - END: Transmision data from device (" + event.getInfoEvents(6));
    //STEP 7 - END: Transmision data from device 
    
    
    ensamble_buffersToData(data, temp_resultDevice);
    if(exec.get_printResults()){
        fileWriter_logFile.write(data.printAll());
    }

    if(compareResults(data)){
        fileWriter_logFile.write("\033[1;32m***WELL, The results match***\033[0m\n");
        result = true;
    }else{
        fileWriter_logFile.write("\033[1;31m***BAD, The results don't match***\033[0m\n");
        result = false;
    }
    fileWriter_logFile.writeln("--------------- Key execution times ---------------");
    fileWriter_logFile.write(event.getInfoEvents());
    fileWriter_logFile.writeln("---------------------------------------------------");
    fileWriter_logFile.writeln("CPU energy consumption           :" + to_string(resultMeasure_CPU) + " Watts");
    fileWriter_logFile.writeln("CPU Opt energy consumption       :" + to_string(resultMeasure_CPUopt) + " Watts");
    for(int i=0 ; i< resultMeasure_CPUopt_byPack.size() ; i++){
        fileWriter_logFile.writeln("\tPack " + to_string(i) + ": " + to_string(resultMeasure_CPUopt_byPack[i]) + " Watts");
    }
    fileWriter_logFile.writeln("Device energy consumption        :" + to_string(resultMeasure_Device) + " Watts");
    fileWriter_logFile.writeln("---------------------------------------------------");


    resultsPerformance.push_back(stod(event.getTimeEvents(1)));                                  //CPU execution time
    resultsPerformance.push_back(stod(event.getTimeEvents(2)));                                  //CPU execution time optimizated
    resultsPerformance.push_back(stod(event.getTimeEvents(5)));                                  //Device execution time 
    resultsPerformance.push_back(stod(event.getTimeEvents(4)) + stod(event.getTimeEvents(6)));   //Transmision (Send+Recv) time
    resultsPerformance.push_back(stod(event.getTimeEvents(4)));                                  //Send to device time
    resultsPerformance.push_back(stod(event.getTimeEvents(6)));                                  //Recieve from device time

    resultsPower.clear();
    resultsPower.push_back(resultMeasure_Device);
    resultsPower.push_back(stod(event.getTimeEvents(5)));       //Device execution time
    resultsPower.push_back(resultMeasure_CPU);
    resultsPower.push_back(stod(event.getTimeEvents(1)));       //CPU execution time
    resultsPower.push_back(resultMeasure_CPUopt);
    resultsPower.push_back(stod(event.getTimeEvents(2)));       //CPU execution time optimizated
    for(int i=0 ; i< resultMeasure_CPUopt_byPack.size() ; i++){
        resultsPower.push_back(resultMeasure_CPUopt_byPack[i]);
    }

  return result;
}
//*************************************
// MAIN FUNCTION - END
//*************************************
bool StudyCase3Host_c::initParameter(Execution exec, unsigned int &SIZE){
    if(exec.get_dataSize() == "mini"){
        SIZE=VECTORADD_SIZE_MINI;
    }else if(exec.get_dataSize() == "small"){
        SIZE=VECTORADD_SIZE_SMALL;
    }else if(exec.get_dataSize() == "medium"){
        SIZE=VECTORADD_SIZE_MEDIUM;
    }else if(exec.get_dataSize() == "large"){
        SIZE=VECTORADD_SIZE_LARGE;
    }else if(exec.get_dataSize() == "extralarge"){
        SIZE=VECTORADD_SIZE_EXTRALARGE;
    }else{
        return false;
    }  
    return true;
}



bool StudyCase3Host_c::compareResults(StudyCase3Kernel& data){

    typeData_fixed tolerance = 0.01;
    typeData_fixed tempDataCPU, tempDataDevice;

    for (int i = 0; i < data.get_resultDevice().size() ; i++) {
        tempDataCPU = data.get_resultCPU()[i];
        tempDataDevice = data.get_resultDevice()[i];
        if( !((tempDataCPU > tempDataDevice ? tempDataCPU - tempDataDevice : tempDataDevice - tempDataCPU) < tolerance) ){
            //cout << i << "  " << data.get_resultCPU()[i] << "  " << data.get_resultDevice()[i] << endl;
            return false;
        }
    }
    return true;
}



void StudyCase3Host_c::ensamble_dataToBuffers(StudyCase3Kernel& data, typeData_fixed *temp_A, typeData_fixed *temp_B, typeData_fixed *temp_resultDevice){

    for (int i = 0; i < data.get_SIZE(); i++) {
        temp_A[i] = data.get_vA()[i];
        temp_B[i] = data.get_vB()[i];
        temp_resultDevice[i]=0.0;
    }

  return;
}



void StudyCase3Host_c::ensamble_buffersToData(StudyCase3Kernel& data, typeData_fixed *temp_resultDevice){
    
    for (int i = 0; i < data.get_SIZE() ; i++) {
        data.get_resultDevice()[i] = temp_resultDevice[i];
    }
    return;
}


double StudyCase3Host_c::executeAndMeasure_CPU(StudyCase3Kernel& data, EventTimer &event){

    cout << "Measuring CPU Power...";
    pthread_t thread;
    int core = 0;
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core, &cpuset);
    function<void()> func = [&data]() { data.kernel_studyCase3_c_CPU(); };
    if (pthread_create(&thread, nullptr, [](void* arg) -> void* {
        auto* func = static_cast<function<void()>*>(arg);
        (*func)();
        return nullptr;
    }, &func) != 0) {
        cerr << "ERROR..: We couldn't create the execution thread" << endl;
        return -1;
    }
    

    long long measureStart_0=0, measureEnd_0=0;
    long long powerUnit=0;
    double powerStart=0, powerEnd=0, powerResult0=0;
    double powerUnitCPU_0=0;

    string file= "/dev/cpu/"+to_string(core)+"/msr";
    int fd0 = open(file.c_str(), O_RDONLY);
    if (fd0 < 0) {
        cerr << "ERROR..: We couldn`t open the MSR file." << endl;
    }
    if (pread(fd0, &powerUnit, sizeof(powerUnit), MSR_RAPL_POWER_UNIT) != sizeof(powerUnit)) {
        cerr << "ERROR..: We couldn't read the MSR(" << MSR_RAPL_POWER_UNIT << ") into MSR file."<< endl;
    }
    powerUnitCPU_0 = pow(0.5,(double)((powerUnit>>8)&0x1f));

    auto start = chrono::high_resolution_clock::now();
    if (pread(fd0, &measureStart_0, sizeof(measureStart_0), MSR_PKG_ENERGY_STATUS) != sizeof(measureStart_0)) {
        cerr << "ERROR..: We couldn't read the MSR(" << MSR_PKG_ENERGY_STATUS << ") into MSR file."<< endl;
    }  

    if (pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset) != 0) {
        cerr << "ERROR..: setting CPU affinity" << endl;
    }
    event.add("Running kernel in CPU");
    if (pthread_join(thread, nullptr) != 0) {
        cerr << "ERROR..: joining thread" << endl;
    }else {
        cout << "Thread running on CPU " << core;
    }
    event.finish();


    if (pread(fd0, &measureEnd_0, sizeof(measureEnd_0), MSR_PKG_ENERGY_STATUS) != sizeof(measureEnd_0)) {
        cerr << "ERROR..: We couldn't read the MSR(" << MSR_PKG_ENERGY_STATUS << ") into MSR file."<< endl;
    }  
    auto end = chrono::high_resolution_clock::now();


    chrono::duration<double> elapsed = end - start;
    powerStart=(double)measureStart_0*powerUnitCPU_0;
    powerEnd=(double)measureEnd_0*powerUnitCPU_0;
    powerResult0 = powerEnd - powerStart;
    powerResult0 = powerResult0/elapsed.count();

    cout << "...Finalizing Measure CPU power ( " << powerResult0 <<" Watts )" << endl;

    return powerResult0;
}



double StudyCase3Host_c::executeAndMeasure_CPUopt(StudyCase3Kernel& data, vector<double> &measureByPack, EventTimer &event){

    cout << "Measuring CPU Power...";
    long long measureStart_0=0, measureEnd_0=0, measureStart_16=0, measureEnd_16=0;
    long long powerUnit=0;
    double powerStart=0, powerEnd=0, powerResult0=0, powerResult16=0;
    double powerUnitCPU_0=0, powerUnitCPU_16=0;

    int fd0 = open("/dev/cpu/0/msr", O_RDONLY);
    if (fd0 < 0) {
        cerr << "ERROR..: We couldn`t open the MSR file." << endl;
    }
    if (pread(fd0, &powerUnit, sizeof(powerUnit), MSR_RAPL_POWER_UNIT) != sizeof(powerUnit)) {
        cerr << "ERROR..: We couldn't read the MSR(" << MSR_RAPL_POWER_UNIT << ") into MSR file."<< endl;
    }
    powerUnitCPU_0 = pow(0.5,(double)((powerUnit>>8)&0x1f));

    int fd16 = open("/dev/cpu/16/msr", O_RDONLY);
    if (fd16 < 0) {
        cerr << "ERROR..: We couldn`t open the MSR file." << endl;
    }
    if (pread(fd16, &powerUnit, sizeof(powerUnit), MSR_RAPL_POWER_UNIT) != sizeof(powerUnit)) {
        cerr << "ERROR..: We couldn't read the MSR(" << MSR_RAPL_POWER_UNIT << ") into MSR file."<< endl;
    }
    powerUnitCPU_16 = pow(0.5,(double)((powerUnit>>8)&0x1f));


    auto start = chrono::high_resolution_clock::now();
    if (pread(fd0, &measureStart_0, sizeof(measureStart_0), MSR_PKG_ENERGY_STATUS) != sizeof(measureStart_0)) {
        cerr << "ERROR..: We couldn't read the MSR(" << MSR_PKG_ENERGY_STATUS << ") into MSR file."<< endl;
    }  
    if (pread(fd16, &measureStart_16, sizeof(measureStart_16), MSR_PKG_ENERGY_STATUS) != sizeof(measureStart_16)) {
        cerr << "ERROR..: We couldn't read the MSR(" << MSR_PKG_ENERGY_STATUS << ") into MSR file."<< endl;
    }  

    event.add("Running kernel in CPU optimizated");
    data.kernel_studyCase3_c_CPU_opt();
    event.finish();


    if (pread(fd0, &measureEnd_0, sizeof(measureEnd_0), MSR_PKG_ENERGY_STATUS) != sizeof(measureEnd_0)) {
        cerr << "ERROR..: We couldn't read the MSR(" << MSR_PKG_ENERGY_STATUS << ") into MSR file."<< endl;
    }  
    if (pread(fd16, &measureEnd_16, sizeof(measureEnd_16), MSR_PKG_ENERGY_STATUS) != sizeof(measureEnd_16)) {
        cerr << "ERROR..: We couldn't read the MSR(" << MSR_PKG_ENERGY_STATUS << ") into MSR file."<< endl;
    }  
    auto end = chrono::high_resolution_clock::now();


    chrono::duration<double> elapsed = end - start;
    powerStart=(double)measureStart_0*powerUnitCPU_0;
    powerEnd=(double)measureEnd_0*powerUnitCPU_0;
    powerResult0 = powerEnd - powerStart;
    powerResult0 = powerResult0/elapsed.count();
    measureByPack.clear();
    measureByPack.push_back(powerResult0);

    powerStart=(double)measureStart_16*powerUnitCPU_16;
    powerEnd=(double)measureEnd_16*powerUnitCPU_16;
    powerResult16 = powerEnd - powerStart;
    powerResult16 = powerResult16/elapsed.count();
    measureByPack.push_back(powerResult16);

    cout << "...Finalizing Measure CPU power ( " << (powerResult0 + powerResult16) <<" Watts | pack0:" << powerResult0 <<" Watts | pack1:" << powerResult16 <<" Watts)." << endl;

    return (powerResult0 + powerResult16);
}



void StudyCase3Host_c::threadFunction_DevicePowerMeasure() {

    cout << "Measuring device Power...";
    unsigned int numIter=0; 

    sharedVariable=0;
    do{
        sharedVariable += searchPropertyValue( xrt::device(0).get_info<xrt::info::device::electrical>(), "power_consumption_watts");
        numIter++;
        this_thread::sleep_for(chrono::milliseconds(1));
    }while (!stop_thread.load());

    sharedVariable = sharedVariable/numIter;
    cout << "...Finalizing Measure device power ("<< sharedVariable <<" Watts  |  " << numIter << " lectures )." << endl;
    return;
}



float StudyCase3Host_c::searchPropertyValue(const string& texto, const string& subcadena) {
    istringstream stream(texto);
    string linea;
    string resultado;

    while (getline(stream, linea)) {
        if (linea.find(subcadena) != string::npos) {
            size_t start = linea.find(":") + 1;
            size_t end = linea.find(",", start);
            if (end == string::npos) {
                end = linea.size();
            }

            resultado = linea.substr(start, end - start);
            resultado.erase(remove(resultado.begin(), resultado.end(), '\"'), resultado.end());
            resultado.erase(remove(resultado.begin(), resultado.end(), ' '), resultado.end());
            return stof(resultado);
        }
    }
    return 0.0f;
}
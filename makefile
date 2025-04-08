CURRENT_DIR := $(shell pwd)
BUILD_DIRECTORY_SW_EMU=build/hostBuild/sw_emu
BUILD_DIRECTORY_HW_EMU=build/hostBuild/hw_emu
BUILD_DIRECTORY_HW=build/hostBuild/hw
CMAKE_DIRECTORY=../../../cmake
SCRIPTS_ROUTE=cmake/scripts/
DEPENDENCIES_SCRIPTS_ROUTE=cmake/scripts/installDependencies.sh

JOBS = 12
REPLACE_FILES = true
CONFIGFILE_ROUTE=../../../config/configTest_gemmPer/configBenchmark_gemmPer.json



#Kernel url specification - START
#***********************************
KERNELS_ROUTE=src/device/

KERNEL_CHOLESKY_OPT0_SUBROUTE=ker_cholesky/ker_cholesky_Opt0
KERNEL_CHOLESKY_OPT0_NAME=makeKer_cholesky_Opt0.mk
KERNEL_CHOLESKY_OPT1_SUBROUTE=ker_cholesky/ker_cholesky_Opt1
KERNEL_CHOLESKY_OPT1_NAME=makeKer_cholesky_Opt1.mk
KERNEL_CHOLESKY_OPT2_SUBROUTE=ker_cholesky/ker_cholesky_Opt2
KERNEL_CHOLESKY_OPT2_NAME=makeKer_cholesky_Opt2.mk
KERNEL_CHOLESKY_OPT3_SUBROUTE=ker_cholesky/ker_cholesky_Opt3
KERNEL_CHOLESKY_OPT3_NAME=makeKer_cholesky_Opt3.mk
KERNEL_CHOLESKY_OPT4_SUBROUTE=ker_cholesky/ker_cholesky_Opt4
KERNEL_CHOLESKY_OPT4_NAME=makeKer_cholesky_Opt4.mk

KERNEL_DOITGEN_OPT0_SUBROUTE=ker_doitgen/ker_doitgen_Opt0
KERNEL_DOITGEN_OPT0_NAME=makeKer_doitgen_Opt0.mk
KERNEL_DOITGEN_OPT1_SUBROUTE=ker_doitgen/ker_doitgen_Opt1
KERNEL_DOITGEN_OPT1_NAME=makeKer_doitgen_Opt1.mk
KERNEL_DOITGEN_OPT2_SUBROUTE=ker_doitgen/ker_doitgen_Opt2
KERNEL_DOITGEN_OPT2_NAME=makeKer_doitgen_Opt2.mk
KERNEL_DOITGEN_OPT3_SUBROUTE=ker_doitgen/ker_doitgen_Opt3
KERNEL_DOITGEN_OPT3_NAME=makeKer_doitgen_Opt3.mk
KERNEL_DOITGEN_OPT4_SUBROUTE=ker_doitgen/ker_doitgen_Opt4
KERNEL_DOITGEN_OPT4_NAME=makeKer_doitgen_Opt4.mk

KERNEL_GEMM_OPT0_SUBROUTE=ker_gemm/ker_gemm_Opt0
KERNEL_GEMM_OPT0_NAME=makeKer_gemm_Opt0.mk
KERNEL_GEMM_OPT1_SUBROUTE=ker_gemm/ker_gemm_Opt1
KERNEL_GEMM_OPT1_NAME=makeKer_gemm_Opt1.mk
KERNEL_GEMM_OPT2_SUBROUTE=ker_gemm/ker_gemm_Opt2
KERNEL_GEMM_OPT2_NAME=makeKer_gemm_Opt2.mk
KERNEL_GEMM_OPT3_SUBROUTE=ker_gemm/ker_gemm_Opt3
KERNEL_GEMM_OPT3_NAME=makeKer_gemm_Opt3.mk
KERNEL_GEMM_OPT4_SUBROUTE=ker_gemm/ker_gemm_Opt4
KERNEL_GEMM_OPT4_NAME=makeKer_gemm_Opt4.mk

KERNEL_GEMMPER_OPT0_SUBROUTE=ker_gemmPer/ker_gemmPer_Opt0
KERNEL_GEMMPER_OPT0_NAME=makeKer_gemmPer_Opt0.mk
KERNEL_GEMMPER_OPT1_SUBROUTE=ker_gemmPer/ker_gemmPer_Opt1
KERNEL_GEMMPER_OPT1_NAME=makeKer_gemmPer_Opt1.mk
KERNEL_GEMMPER_OPT2_SUBROUTE=ker_gemmPer/ker_gemmPer_Opt2
KERNEL_GEMMPER_OPT2_NAME=makeKer_gemmPer_Opt2.mk
KERNEL_GEMMPER_OPT3_SUBROUTE=ker_gemmPer/ker_gemmPer_Opt3
KERNEL_GEMMPER_OPT3_NAME=makeKer_gemmPer_Opt3.mk
KERNEL_GEMMPER_OPT4_SUBROUTE=ker_gemmPer/ker_gemmPer_Opt4
KERNEL_GEMMPER_OPT4_NAME=makeKer_gemmPer_Opt4.mk

KERNEL_JACOBI2D_OPT0_SUBROUTE=ker_jacobi2d/ker_jacobi2d_Opt0
KERNEL_JACOBI2D_OPT0_NAME=makeKer_jacobi2d_Opt0.mk
KERNEL_JACOBI2D_OPT1_SUBROUTE=ker_jacobi2d/ker_jacobi2d_Opt1
KERNEL_JACOBI2D_OPT1_NAME=makeKer_jacobi2d_Opt1.mk
KERNEL_JACOBI2D_OPT2_SUBROUTE=ker_jacobi2d/ker_jacobi2d_Opt2
KERNEL_JACOBI2D_OPT2_NAME=makeKer_jacobi2d_Opt2.mk
KERNEL_JACOBI2D_OPT3_SUBROUTE=ker_jacobi2d/ker_jacobi2d_Opt3
KERNEL_JACOBI2D_OPT3_NAME=makeKer_jacobi2d_Opt3.mk
KERNEL_JACOBI2D_OPT4_SUBROUTE=ker_jacobi2d/ker_jacobi2d_Opt4
KERNEL_JACOBI2D_OPT4_NAME=makeKer_jacobi2d_Opt4.mk

KERNEL_VECTORADD_OPT0_SUBROUTE=ker_vectorAdd/ker_vectorAdd_Opt0
KERNEL_VECTORADD_OPT0_NAME=makeKer_vectorAdd_Opt0.mk
KERNEL_VECTORADD_OPT1_SUBROUTE=ker_vectorAdd/ker_vectorAdd_Opt1
KERNEL_VECTORADD_OPT1_NAME=makeKer_vectorAdd_Opt1.mk
KERNEL_VECTORADD_OPT2_SUBROUTE=ker_vectorAdd/ker_vectorAdd_Opt2
KERNEL_VECTORADD_OPT2_NAME=makeKer_vectorAdd_Opt2.mk
KERNEL_VECTORADD_OPT3_SUBROUTE=ker_vectorAdd/ker_vectorAdd_Opt3
KERNEL_VECTORADD_OPT3_NAME=makeKer_vectorAdd_Opt3.mk
KERNEL_VECTORADD_OPT4_SUBROUTE=ker_vectorAdd/ker_vectorAdd_Opt4
KERNEL_VECTORADD_OPT4_NAME=makeKer_vectorAdd_Opt4.mk

KERNEL_STUDYCASE1_A_SUBROUTE=ker_studyCase1/ker_studyCase1_a
KERNEL_STUDYCASE1_A_NAME=makeKer_studyCase1_a.mk
KERNEL_STUDYCASE1_B_SUBROUTE=ker_studyCase1/ker_studyCase1_b
KERNEL_STUDYCASE1_B_NAME=makeKer_studyCase1_b.mk
KERNEL_STUDYCASE1_C_SUBROUTE=ker_studyCase1/ker_studyCase1_c
KERNEL_STUDYCASE1_C_NAME=makeKer_studyCase1_c.mk

KERNEL_STUDYCASE2_A_SUBROUTE=ker_studyCase2/ker_studyCase2_a
KERNEL_STUDYCASE2_A_NAME=makeKer_studyCase2_a.mk
KERNEL_STUDYCASE2_B_SUBROUTE=ker_studyCase2/ker_studyCase2_b
KERNEL_STUDYCASE2_B_NAME=makeKer_studyCase2_b.mk
KERNEL_STUDYCASE2_C_SUBROUTE=ker_studyCase2/ker_studyCase2_c
KERNEL_STUDYCASE2_C_NAME=makeKer_studyCase2_c.mk
KERNEL_STUDYCASE2_D_SUBROUTE=ker_studyCase2/ker_studyCase2_d
KERNEL_STUDYCASE2_D_NAME=makeKer_studyCase2_d.mk

KERNEL_STUDYCASE3_A_SUBROUTE=ker_studyCase3/ker_studyCase3_a
KERNEL_STUDYCASE3_A_NAME=makeKer_studyCase3_a.mk
KERNEL_STUDYCASE3_B_SUBROUTE=ker_studyCase3/ker_studyCase3_b
KERNEL_STUDYCASE3_B_NAME=makeKer_studyCase3_b.mk
KERNEL_STUDYCASE3_C_SUBROUTE=ker_studyCase3/ker_studyCase3_c
KERNEL_STUDYCASE3_C_NAME=makeKer_studyCase3_c.mk
KERNEL_STUDYCASE3_D_SUBROUTE=ker_studyCase3/ker_studyCase3_d
KERNEL_STUDYCASE3_D_NAME=makeKer_studyCase3_d.mk
#***********************************
#Kernel url specification - END




.phony: clean build

#**********************************************
# COMMANDS FOR CHOLESKY KERNELS COMPILE - START
#**********************************************
# KERNEL TARGET sw_emu
#*********************************
kerCholesky_Opt0_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT0_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT0_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerCholesky_Opt1_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT1_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT1_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerCholesky_Opt2_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT2_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT2_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerCholesky_Opt3_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT3_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT3_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerCholesky_Opt4_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT4_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT4_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerCholesky_All_build_sw_emu: kerCholesky_Opt0_build_sw_emu kerCholesky_Opt1_build_sw_emu kerCholesky_Opt2_build_sw_emu kerCholesky_Opt3_build_sw_emu kerCholesky_Opt4_build_sw_emu


# KERNEL TARGET hw_emu
#*********************************
kerCholesky_Opt0_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT0_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT0_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerCholesky_Opt1_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT1_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT1_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerCholesky_Opt2_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT2_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT2_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerCholesky_Opt3_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT3_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT3_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerCholesky_Opt4_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT4_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT4_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerCholesky_All_build_hw_emu: kerCholesky_Opt0_build_hw_emu kerCholesky_Opt1_build_hw_emu kerCholesky_Opt2_build_hw_emu kerCholesky_Opt3_build_hw_emu kerCholesky_Opt4_build_hw_emu


# KERNEL TARGET hw
#*********************************
kerCholesky_Opt0_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT0_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT0_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerCholesky_Opt1_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT1_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT1_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerCholesky_Opt2_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT2_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT2_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerCholesky_Opt3_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT3_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT3_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerCholesky_Opt4_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_CHOLESKY_OPT4_SUBROUTE}; \
	make -f $(KERNEL_CHOLESKY_OPT4_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerCholesky_All_build_hw: kerCholesky_Opt0_build_hw kerCholesky_Opt1_build_hw kerCholesky_Opt2_build_hw kerCholesky_Opt3_build_hw kerCholesky_Opt4_build_hw
#**********************************************
# COMMANDS FOR CHOLESKY KERNELS COMPILE - END
#**********************************************





#*********************************************
# COMMANDS FOR DOITGEN KERNELS COMPILE - START
#*********************************************
# KERNEL TARGET sw_emu
#*********************************
kerDoitgen_Opt0_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT0_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT0_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerDoitgen_Opt1_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT1_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT1_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerDoitgen_Opt2_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT2_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT2_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerDoitgen_Opt3_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT3_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT3_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerDoitgen_Opt4_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT4_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT4_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerDoitgen_All_build_sw_emu: kerDoitgen_Opt0_build_sw_emu kerDoitgen_Opt1_build_sw_emu kerDoitgen_Opt2_build_sw_emu kerDoitgen_Opt3_build_sw_emu kerDoitgen_Opt4_build_sw_emu


# KERNEL TARGET hw_emu
#*********************************
kerDoitgen_Opt0_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT0_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT0_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerDoitgen_Opt1_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT1_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT1_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerDoitgen_Opt2_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT2_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT2_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerDoitgen_Opt3_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT3_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT3_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerDoitgen_Opt4_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT4_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT4_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerDoitgen_All_build_hw_emu: kerDoitgen_Opt0_build_hw_emu kerDoitgen_Opt1_build_hw_emu kerDoitgen_Opt2_build_hw_emu kerDoitgen_Opt3_build_hw_emu kerDoitgen_Opt4_build_hw_emu


# KERNEL TARGET hw
#*********************************
kerDoitgen_Opt0_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT0_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT0_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerDoitgen_Opt1_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT1_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT1_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerDoitgen_Opt2_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT2_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT2_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerDoitgen_Opt3_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT3_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT3_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerDoitgen_Opt4_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_DOITGEN_OPT4_SUBROUTE}; \
	make -f $(KERNEL_DOITGEN_OPT4_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerDoitgen_All_build_hw: kerDoitgen_Opt0_build_hw kerDoitgen_Opt1_build_hw kerDoitgen_Opt2_build_hw kerDoitgen_Opt3_build_hw kerDoitgen_Opt4_build_hw
#*********************************************
# COMMANDS FOR DOITGEN KERNELS COMPILE - END
#*********************************************





#******************************************
# COMMANDS FOR GEMM KERNELS COMPILE - START
#******************************************
# KERNEL TARGET sw_emu
#*********************************
kerGemm_Opt0_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT0_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT0_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerGemm_Opt1_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT1_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT1_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemm_Opt2_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT2_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT2_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerGemm_Opt3_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT3_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT3_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemm_Opt4_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT4_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT4_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemm_All_build_sw_emu: kerGemm_Opt0_build_sw_emu kerGemm_Opt1_build_sw_emu kerGemm_Opt2_build_sw_emu kerGemm_Opt3_build_sw_emu kerGemm_Opt4_build_sw_emu


# KERNEL TARGET hw_emu
#*********************************
kerGemm_Opt0_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT0_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT0_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerGemm_Opt1_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT1_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT1_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemm_Opt2_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT2_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT2_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerGemm_Opt3_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT3_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT3_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemm_Opt4_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT4_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT4_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemm_All_build_hw_emu: kerGemm_Opt0_build_hw_emu kerGemm_Opt1_build_hw_emu kerGemm_Opt2_build_hw_emu kerGemm_Opt3_build_hw_emu kerGemm_Opt4_build_hw_emu


# KERNEL TARGET hw
#*********************************
kerGemm_Opt0_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT0_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT0_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerGemm_Opt1_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT1_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT1_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemm_Opt2_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT2_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT2_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerGemm_Opt3_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT3_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT3_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemm_Opt4_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMM_OPT4_SUBROUTE}; \
	make -f $(KERNEL_GEMM_OPT4_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemm_All_build_hw: kerGemm_Opt0_build_hw kerGemm_Opt1_build_hw kerGemm_Opt2_build_hw kerGemm_Opt3_build_hw kerGemm_Opt4_build_hw
#******************************************
# COMMANDS FOR GEMM KERNELS COMPILE - END
#******************************************





#**********************************************
# COMMANDS FOR GEMM_PER KERNELS COMPILE - START
#**********************************************
# KERNEL TARGET sw_emu
#*********************************
kerGemmPer_Opt0_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT0_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT0_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerGemmPer_Opt1_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT1_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT1_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemmPer_Opt2_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT2_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT2_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerGemmPer_Opt3_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT3_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT3_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemmPer_Opt4_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT4_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT4_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemmPer_All_build_sw_emu: kerGemmPer_Opt0_build_sw_emu kerGemmPer_Opt1_build_sw_emu kerGemmPer_Opt2_build_sw_emu kerGemmPer_Opt3_build_sw_emu kerGemmPer_Opt4_build_sw_emu


# KERNEL TARGET hw_emu
#*********************************
kerGemmPer_Opt0_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT0_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT0_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerGemmPer_Opt1_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT1_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT1_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemmPer_Opt2_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT2_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT2_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerGemmPer_Opt3_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT3_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT3_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemmPer_Opt4_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT4_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT4_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemmPer_All_build_hw_emu: kerGemmPer_Opt0_build_hw_emu kerGemmPer_Opt1_build_hw_emu kerGemmPer_Opt2_build_hw_emu kerGemmPer_Opt3_build_hw_emu kerGemmPer_Opt4_build_hw_emu


# KERNEL TARGET hw
#*********************************
kerGemmPer_Opt0_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT0_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT0_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerGemmPer_Opt1_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT1_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT1_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemmPer_Opt2_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT2_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT2_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemmPer_Opt3_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT3_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT3_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemmPer_Opt4_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_GEMMPER_OPT4_SUBROUTE}; \
	make -f $(KERNEL_GEMMPER_OPT4_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerGemmPer_All_build_hw: kerGemmPer_Opt0_build_hw kerGemmPer_Opt1_build_hw kerGemmPer_Opt2_build_hw kerGemmPer_Opt3_build_hw kerGemmPer_Opt4_build_hw
#**********************************************
# COMMANDS FOR GEMM_PER KERNELS COMPILE - END
#**********************************************





#***********************************************
# COMMANDS FOR JACOBI_2D KERNELS COMPILE - START
#***********************************************
# KERNEL TARGET sw_emu
#*********************************
kerJacobi2d_Opt0_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT0_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT0_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerJacobi2d_Opt1_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT1_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT1_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerJacobi2d_Opt2_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT2_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT2_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerJacobi2d_Opt3_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT3_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT3_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerJacobi2d_Opt4_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT4_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT4_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerJacobi2d_All_build_sw_emu: kerJacobi2d_Opt0_build_sw_emu kerJacobi2d_Opt1_build_sw_emu kerJacobi2d_Opt2_build_sw_emu kerJacobi2d_Opt3_build_sw_emu kerJacobi2d_Opt4_build_sw_emu


# KERNEL TARGET hw_emu
#*********************************
kerJacobi2d_Opt0_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT0_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT0_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerJacobi2d_Opt1_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT1_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT1_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerJacobi2d_Opt2_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT2_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT2_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerJacobi2d_Opt3_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT3_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT3_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerJacobi2d_Opt4_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT4_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT4_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerJacobi2d_All_build_hw_emu: kerJacobi2d_Opt0_build_hw_emu kerJacobi2d_Opt1_build_hw_emu kerJacobi2d_Opt2_build_hw_emu kerJacobi2d_Opt3_build_hw_emu kerJacobi2d_Opt4_build_hw_emu


# KERNEL TARGET hw
#*********************************
kerJacobi2d_Opt0_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT0_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT0_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerJacobi2d_Opt1_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT1_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT1_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerJacobi2d_Opt2_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT2_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT2_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerJacobi2d_Opt3_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT3_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT3_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerJacobi2d_Opt4_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_JACOBI2D_OPT4_SUBROUTE}; \
	make -f $(KERNEL_JACOBI2D_OPT4_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerJacobi2d_All_build_hw: kerJacobi2d_Opt0_build_hw kerJacobi2d_Opt1_build_hw kerJacobi2d_Opt2_build_hw kerJacobi2d_Opt3_build_hw kerJacobi2d_Opt4_build_hw
#***********************************************
# COMMANDS FOR JACOBI_2D KERNELS COMPILE - START
#***********************************************



#***********************************************
# COMMANDS FOR VECTORADD KERNELS COMPILE - START
#***********************************************
# KERNEL TARGET sw_emu
#*********************************
kerVectorAdd_Opt0_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT0_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT0_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerVectorAdd_Opt1_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT1_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT1_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerVectorAdd_Opt2_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT2_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT2_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerVectorAdd_Opt3_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT3_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT3_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerVectorAdd_Opt4_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT4_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT4_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerVectorAdd_All_build_sw_emu: kerVectorAdd_Opt0_build_sw_emu kerVectorAdd_Opt1_build_sw_emu kerVectorAdd_Opt2_build_sw_emu kerVectorAdd_Opt3_build_sw_emu kerVectorAdd_Opt4_build_sw_emu


# KERNEL TARGET hw_emu
#*********************************
kerVectorAdd_Opt0_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT0_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT0_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerVectorAdd_Opt1_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT1_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT1_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerVectorAdd_Opt2_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT2_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT2_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerVectorAdd_Opt3_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT3_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT3_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerVectorAdd_Opt4_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT4_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT4_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerVectorAdd_All_build_hw_emu: kerVectorAdd_Opt0_build_hw_emu kerVectorAdd_Opt1_build_hw_emu kerVectorAdd_Opt2_build_hw_emu kerVectorAdd_Opt3_build_hw_emu kerVectorAdd_Opt4_build_hw_emu


# KERNEL TARGET hw
#*********************************
kerVectorAdd_Opt0_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT0_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT0_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerVectorAdd_Opt1_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT1_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT1_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerVectorAdd_Opt2_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT2_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT2_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerVectorAdd_Opt3_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT3_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT3_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerVectorAdd_Opt4_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_VECTORADD_OPT4_SUBROUTE}; \
	make -f $(KERNEL_VECTORADD_OPT4_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerVectorAdd_All_build_hw: kerVectorAdd_Opt0_build_hw kerVectorAdd_Opt1_build_hw kerVectorAdd_Opt2_build_hw kerVectorAdd_Opt3_build_hw kerVectorAdd_Opt4_build_hw
#***********************************************
# COMMANDS FOR JACOBI_2D KERNELS COMPILE - START
#***********************************************



#***********************************************
# COMMANDS FOR STUDYCASE1 KERNELS COMPILE - START
#***********************************************
# KERNEL TARGET sw_emu
#*********************************
kerStudyCase1_a_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE1_A_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE1_A_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerStudyCase1_b_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE1_B_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE1_B_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase1_c_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE1_C_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE1_C_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase1_All_build_sw_emu: kerStudyCase1_a_build_sw_emu kerStudyCase1_b_build_sw_emu kerStudyCase1_c_build_sw_emu


# KERNEL TARGET hw_emu
#*********************************
kerStudyCase1_a_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE1_A_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE1_A_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerStudyCase1_b_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE1_B_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE1_B_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase1_c_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE1_C_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE1_C_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase1_All_build_hw_emu: kerStudyCase1_a_build_hw_emu kerStudyCase1_b_build_hw_emu kerStudyCase1_c_build_hw_emu


# KERNEL TARGET hw
#*********************************
kerStudyCase1_a_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE1_A_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE1_A_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerStudyCase1_b_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE1_B_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE1_B_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase1_c_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE1_C_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE1_C_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase1_All_build_hw: kerStudyCase1_a_build_hw kerStudyCase1_b_build_hw kerStudyCase1_c_build_hw
#***********************************************
# COMMANDS FOR STUDYCASE1 KERNELS COMPILE - START
#***********************************************



#***********************************************
# COMMANDS FOR STUDYCASE2 KERNELS COMPILE - START
#***********************************************
# KERNEL TARGET sw_emu
#*********************************
kerStudyCase2_a_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE2_A_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE2_A_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerStudyCase2_b_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE2_B_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE2_B_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase2_c_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE2_C_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE2_C_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase2_d_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE2_D_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE2_D_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase2_All_build_sw_emu: kerStudyCase2_a_build_sw_emu kerStudyCase2_b_build_sw_emu kerStudyCase2_c_build_sw_emu kerStudyCase2_d_build_sw_emu


# KERNEL TARGET hw_emu
#*********************************
kerStudyCase2_a_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE2_A_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE2_A_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerStudyCase2_b_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE2_B_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE2_B_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase2_c_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE2_C_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE2_C_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase2_d_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE2_D_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE2_D_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase2_All_build_hw_emu: kerStudyCase2_a_build_hw_emu kerStudyCase2_b_build_hw_emu kerStudyCase2_c_build_hw_emu kerStudyCase2_d_build_hw_emu


# KERNEL TARGET hw
#*********************************
kerStudyCase2_a_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE2_A_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE2_A_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerStudyCase2_b_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE2_B_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE2_B_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase2_c_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE2_C_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE2_C_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase2_d_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE2_D_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE2_D_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase2_All_build_hw: kerStudyCase2_a_build_hw kerStudyCase2_b_build_hw kerStudyCase2_c_build_hw kerStudyCase2_d_build_hw
#***********************************************
# COMMANDS FOR STUDYCASE2 KERNELS COMPILE - START
#***********************************************


#***********************************************
# COMMANDS FOR STUDYCASE3 KERNELS COMPILE - START
#***********************************************
# KERNEL TARGET sw_emu
#*********************************
kerStudyCase3_a_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE3_A_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE3_A_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerStudyCase3_b_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE3_B_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE3_B_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase3_c_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE3_C_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE3_C_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase3_d_build_sw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE3_D_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE3_D_NAME) TARGET=sw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase3_All_build_sw_emu: kerStudyCase3_a_build_sw_emu kerStudyCase3_b_build_sw_emu kerStudyCase3_c_build_sw_emu kerStudyCase3_d_build_sw_emu


# KERNEL TARGET hw_emu
#*********************************
kerStudyCase3_a_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE3_A_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE3_A_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerStudyCase3_b_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE3_B_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE3_B_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase3_c_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE3_C_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE3_C_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase3_d_build_hw_emu:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE3_D_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE3_D_NAME) TARGET=hw_emu JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase3_All_build_hw_emu: kerStudyCase3_a_build_hw_emu kerStudyCase3_b_build_hw_emu kerStudyCase3_c_build_hw_emu kerStudyCase3_d_build_hw_emu



# KERNEL TARGET hw
#*********************************
kerStudyCase3_a_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE3_A_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE3_A_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);
	
kerStudyCase3_b_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE3_B_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE3_B_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase3_c_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE3_C_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE3_C_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase3_d_build_hw:
	@cd ${KERNELS_ROUTE}${KERNEL_STUDYCASE3_D_SUBROUTE}; \
	make -f $(KERNEL_STUDYCASE3_D_NAME) TARGET=hw JOBS=$(JOBS) build;
	@cd $(CURRENT_DIR);

kerStudyCase3_All_build_hw: kerStudyCase3_a_build_hw kerStudyCase3_b_build_hw kerStudyCase3_c_build_hw kerStudyCase3_d_build_hw
#***********************************************
# COMMANDS FOR STUDYCASE3 KERNELS COMPILE - START
#***********************************************



#**************************************
# COMMANDS FOR ALL KERNELS COMPILE
#**************************************
kerAll_build_sw_emu: kerCholesky_Opt0_build_sw_emu kerDoitgen_Opt0_build_sw_emu kerGemm_Opt0_build_sw_emu kerGemmPer_Opt0_build_sw_emu kerJacobi2d_Opt0_build_sw_emu kerVectorAdd_All_build_sw_emu
	
kerAll_build_hw_emu: kerCholesky_Opt0_build_hw_emu kerDoitgen_Opt0_build_hw_emu kerGemm_Opt0_build_hw_emu kerGemmPer_Opt0_build_hw_emu kerJacobi2d_Opt0_build_hw_emu kerVectorAdd_All_build_hw_emu
	
kerAll_build_hw: kerCholesky_Opt0_build_hw kerDoitgen_Opt0_build_hw kerGemm_Opt0_build_hw kerGemmPer_Opt0_build_hw kerJacobi2d_Opt0_build_hw kerVectorAdd_All_build_hw




#**************************************
# COMMANDS FOR SOFTWARE COMPILE
#**************************************
hostBuild_sw_emu:
	mkdir -p ${BUILD_DIRECTORY_SW_EMU};
	cd $(BUILD_DIRECTORY_SW_EMU); \
	emconfigutil --platform xilinx_u200_gen3x16_xdma_2_202110_1; \
	cmake -DTARGET=sw_emu -DREPLACE_FILES=${REPLACE_FILES} $(CMAKE_DIRECTORY); \
	make -j

hostBuild_hw_emu:
	mkdir -p ${BUILD_DIRECTORY_HW_EMU};
	@cd $(BUILD_DIRECTORY_HW_EMU); \
	emconfigutil --platform xilinx_u200_gen3x16_xdma_2_202110_1; \
	cmake -DTARGET=hw_emu -DREPLACE_FILES=${REPLACE_FILES} $(CMAKE_DIRECTORY); \
	make -j

hostBuild_hw:
	mkdir -p ${BUILD_DIRECTORY_HW};
	cd $(BUILD_DIRECTORY_HW); \
	emconfigutil --platform xilinx_u200_gen3x16_xdma_2_202110_1; \
	cmake -DTARGET=hw -DREPLACE_FILES=${REPLACE_FILES} $(CMAKE_DIRECTORY); \
	make -j


run_sw_emu:
	@cd $(BUILD_DIRECTORY_SW_EMU); \
	./benchmarkExec $(CONFIGFILE_ROUTE); \

run_hw_emu:
	@cd $(BUILD_DIRECTORY_HW_EMU); \
	./benchmarkExec $(CONFIGFILE_ROUTE); \

run_hw:
	@cd $(BUILD_DIRECTORY_HW); \
	./benchmarkExec $(CONFIGFILE_ROUTE); \


#**************************************
# OTHER COMMANDS
#**************************************
clean_host:
	rm -rf build/hostBuild/*
	rm -rf build/hostBuild/.run
	rm -rf build/hostBuild/.Xil

clean_kernels:
	rm -rf build/kernelBuild/*
	rm -rf build/kernelBuild/.run
	rm -rf build/kernelBuild/.Xil

clean_out:
	rm -rf out/*

install_dependencies:
	./$(DEPENDENCIES_SCRIPTS_ROUTE)
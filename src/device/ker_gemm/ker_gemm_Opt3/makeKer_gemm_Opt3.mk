#**********************
#* CHECK ENTRY PARAMS *
#**********************
ifeq ($(TARGET),sw_emu)
	KERNEL_BUILD_SUBFOLDER := ker_gemm_Opt3/sw_emu/
else ifeq ($(TARGET),hw_emu)
	KERNEL_BUILD_SUBFOLDER := ker_gemm_Opt3/hw_emu/
else ifeq ($(TARGET),hw)
	KERNEL_BUILD_SUBFOLDER := ker_gemm_Opt3/hw/
else
    @echo "Incorret value of TARGET. Please, try again using: make -f <makeFileName> TARGET=sw_emu|hw_emu|hw"
    $(error "Incorret value of TARGET. Please, try again using: make -f <makeFileName> TARGET=sw_emu|hw_emu|hw")
	exit -1
endif

ifndef JOBS
	NCPUS := $(shell grep -c ^processor /proc/cpuinfo)
	JOBS := $(shell expr $(NCPUS) - 1)
endif


#*****************************
#* CONFIG COMPULATION PARAMS *
#*****************************
PLATFORM ?= xilinx_u200_gen3x16_xdma_2_202110_1
PLATFORM_REPO_PATHS ?= /opt/xilinx/platforms
PFM := $(PLATFORM_REPO_PATHS)/$(PLATFORM)/$(PLATFORM).xpfm
IP_CACHE_DIR ?= ip_cache
VPPFLAGS_GENERAL := --platform $(PFM) -t $(TARGET) -s -g --hls.jobs $(JOBS) --vivado.synth.jobs $(JOBS) --vivado.impl.jobs $(JOBS)



BUILD_DIR := ../../../../build/kernelBuild

CONNECTIVITY_FOLDER := connectivityConfig/
CONNECTIVITY_NAME_MINI := gemm_Opt3_mini_connec.ini
CONNECTIVITY_NAME_SMALL := gemm_Opt3_small_connec.ini
CONNECTIVITY_NAME_MEDIUM := gemm_Opt3_medium_connec.ini
CONNECTIVITY_NAME_LARGE := gemm_Opt3_large_connec.ini
CONNECTIVITY_NAME_EXTRALARGE := gemm_Opt3_extralarge_connec.ini

PROFILE_FOLDER := connectivityConfig/
PROFILE_NAME := profile.ini



VPPLFLAGS_SPECIFIC_MINI := --config $(CONNECTIVITY_NAME_MINI) --config $(PROFILE_NAME) 
VPPLFLAGS_SPECIFIC_SMALL := --config $(CONNECTIVITY_NAME_SMALL) --config $(PROFILE_NAME) 
VPPLFLAGS_SPECIFIC_MEDIUM := --config $(CONNECTIVITY_NAME_MEDIUM) --config $(PROFILE_NAME) 
VPPLFLAGS_SPECIFIC_LARGE := --config $(CONNECTIVITY_NAME_LARGE) --config $(PROFILE_NAME) 
VPPLFLAGS_SPECIFIC_EXTRALARGE := --config $(CONNECTIVITY_NAME_EXTRALARGE) --config $(PROFILE_NAME) 



#********************************************
#* COMPILATION OF kergemm_Opt3imization *
#********************************************
MAKEFILE_NAME := makeKer_gemm_Opt3.mk

PackKerList := kerPack_gemm_Opt3_mini
PackKerList += kerPack_gemm_Opt3_small
PackKerList += kerPack_gemm_Opt3_medium
PackKerList += kerPack_gemm_Opt3_large
PackKerList += kerPack_gemm_Opt3_extralarge


ker_gemm_Opt3_mini_XOS := ker_gemm_Opt3_mini.xo
ker_gemm_Opt3_small_XOS := ker_gemm_Opt3_small.xo
ker_gemm_Opt3_medium_XOS := ker_gemm_Opt3_medium.xo
ker_gemm_Opt3_large_XOS := ker_gemm_Opt3_large.xo
ker_gemm_Opt3_extralarge_XOS := ker_gemm_Opt3_extralarge.xo

ker_gemm_Opt3_mini_KERNEL := ker_gemm_Opt3_mini
ker_gemm_Opt3_small_KERNEL := ker_gemm_Opt3_small
ker_gemm_Opt3_medium_KERNEL := ker_gemm_Opt3_medium
ker_gemm_Opt3_large_KERNEL := ker_gemm_Opt3_large
ker_gemm_Opt3_extralarge_KERNEL := ker_gemm_Opt3_extralarge


ker_gemm_Opt3_mini_CUSTOMPARAMS := -DMINI_DATASET
ker_gemm_Opt3_small_CUSTOMPARAMS := -DSMALL_DATASET
ker_gemm_Opt3_medium_CUSTOMPARAMS := -DMEDIUM_DATASET
ker_gemm_Opt3_large_CUSTOMPARAMS := -DLARGE_DATASET
ker_gemm_Opt3_extralarge_CUSTOMPARAMS := -DEXTRALARGE_DATASET


ker_gemm_Opt3_SRC := ker_gemm_Opt3.cpp
ker_gemm_Opt3_HEADER :=


#********************
#* GOALS DEFINITION *
#********************
build: copy_files

copy_files:
	mkdir -p ${BUILD_DIR};
	mkdir -p ${BUILD_DIR}/${KERNEL_BUILD_SUBFOLDER};
	cp -r ${CONNECTIVITY_FOLDER}${CONNECTIVITY_NAME_MINI} ${BUILD_DIR}/${KERNEL_BUILD_SUBFOLDER};
	cp -r ${CONNECTIVITY_FOLDER}${CONNECTIVITY_NAME_SMALL} ${BUILD_DIR}/${KERNEL_BUILD_SUBFOLDER};
	cp -r ${CONNECTIVITY_FOLDER}${CONNECTIVITY_NAME_MEDIUM} ${BUILD_DIR}/${KERNEL_BUILD_SUBFOLDER};
	cp -r ${CONNECTIVITY_FOLDER}${CONNECTIVITY_NAME_LARGE} ${BUILD_DIR}/${KERNEL_BUILD_SUBFOLDER};
	cp -r ${CONNECTIVITY_FOLDER}${CONNECTIVITY_NAME_EXTRALARGE} ${BUILD_DIR}/${KERNEL_BUILD_SUBFOLDER};
	cp -r ${PROFILE_FOLDER}${PROFILE_NAME} ${BUILD_DIR}/${KERNEL_BUILD_SUBFOLDER};
	cp -r ${ker_gemm_Opt3_SRC} ${BUILD_DIR}/${KERNEL_BUILD_SUBFOLDER};
	cp -r ${MAKEFILE_NAME} ${BUILD_DIR}/${KERNEL_BUILD_SUBFOLDER};
	$(foreach val,$(PackKerList), \
		$(if $(filter $(TARGET),sw_emu), \
			cd ${BUILD_DIR}/${KERNEL_BUILD_SUBFOLDER}; \
			make -f $(MAKEFILE_NAME) TARGET=$(TARGET) $(val)_sw_emu.xclbin;, \
		$(if $(filter $(TARGET),hw_emu), \
			cd ${BUILD_DIR}/${KERNEL_BUILD_SUBFOLDER}; \
			make -f $(MAKEFILE_NAME) TARGET=$(TARGET) $(val)_hw_emu.xclbin;, \
		$(if $(filter $(TARGET),hw), \
			cd ${BUILD_DIR}/${KERNEL_BUILD_SUBFOLDER}; \
			make -f $(MAKEFILE_NAME) TARGET=$(TARGET) $(val)_hw.xclbin;, \
		$(error Error: TARGET $(TARGET) is not recognized.) \
	))))






kerPack_gemm_Opt3_mini_sw_emu.xclbin: $(ker_gemm_Opt3_mini_XOS) $(CONNECTIVITY_NAME_MINI)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_MINI) -o $@ $(ker_gemm_Opt3_mini_XOS) --remote_ip_cache ${IP_CACHE_DIR}

kerPack_gemm_Opt3_small_sw_emu.xclbin: $(ker_gemm_Opt3_small_XOS) $(CONNECTIVITY_NAME_SMALL)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_SMALL) -o $@ $(ker_gemm_Opt3_small_XOS) --remote_ip_cache ${IP_CACHE_DIR}

kerPack_gemm_Opt3_medium_sw_emu.xclbin: $(ker_gemm_Opt3_medium_XOS) $(CONNECTIVITY_NAME_MEDIUM)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_MEDIUM) -o $@ $(ker_gemm_Opt3_medium_XOS) --remote_ip_cache ${IP_CACHE_DIR}

kerPack_gemm_Opt3_large_sw_emu.xclbin: $(ker_gemm_Opt3_large_XOS) $(CONNECTIVITY_NAME_LARGE)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_LARGE) -o $@ $(ker_gemm_Opt3_large_XOS) --remote_ip_cache ${IP_CACHE_DIR}

kerPack_gemm_Opt3_extralarge_sw_emu.xclbin: $(ker_gemm_Opt3_extralarge_XOS) $(CONNECTIVITY_NAME_EXTRALARGE)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_EXTRALARGE) -o $@ $(ker_gemm_Opt3_extralarge_XOS) --remote_ip_cache ${IP_CACHE_DIR}



kerPack_gemm_Opt3_mini_hw_emu.xclbin: $(ker_gemm_Opt3_mini_XOS) $(CONNECTIVITY_NAME_MINI)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_MINI) -o $@ $(ker_gemm_Opt3_mini_XOS) --remote_ip_cache ${IP_CACHE_DIR}

kerPack_gemm_Opt3_small_hw_emu.xclbin: $(ker_gemm_Opt3_small_XOS) $(CONNECTIVITY_NAME_SMALL)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_SMALL) -o $@ $(ker_gemm_Opt3_small_XOS) --remote_ip_cache ${IP_CACHE_DIR}

kerPack_gemm_Opt3_medium_hw_emu.xclbin: $(ker_gemm_Opt3_medium_XOS) $(CONNECTIVITY_NAME_MEDIUM)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_MEDIUM) -o $@ $(ker_gemm_Opt3_medium_XOS) --remote_ip_cache ${IP_CACHE_DIR}

kerPack_gemm_Opt3_large_hw_emu.xclbin: $(ker_gemm_Opt3_large_XOS) $(CONNECTIVITY_NAME_LARGE)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_LARGE) -o $@ $(ker_gemm_Opt3_large_XOS) --remote_ip_cache ${IP_CACHE_DIR}

kerPack_gemm_Opt3_extralarge_hw_emu.xclbin: $(ker_gemm_Opt3_extralarge_XOS) $(CONNECTIVITY_NAME_EXTRALARGE)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_EXTRALARGE) -o $@ $(ker_gemm_Opt3_extralarge_XOS) --remote_ip_cache ${IP_CACHE_DIR}



kerPack_gemm_Opt3_mini_hw.xclbin: $(ker_gemm_Opt3_mini_XOS) $(CONNECTIVITY_NAME_MINI)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_MINI) -o $@ $(ker_gemm_Opt3_mini_XOS) --remote_ip_cache ${IP_CACHE_DIR}

kerPack_gemm_Opt3_small_hw.xclbin: $(ker_gemm_Opt3_small_XOS) $(CONNECTIVITY_NAME_SMALL)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_SMALL) -o $@ $(ker_gemm_Opt3_small_XOS) --remote_ip_cache ${IP_CACHE_DIR}

kerPack_gemm_Opt3_medium_hw.xclbin: $(ker_gemm_Opt3_medium_XOS) $(CONNECTIVITY_NAME_MEDIUM)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_MEDIUM) -o $@ $(ker_gemm_Opt3_medium_XOS) --remote_ip_cache ${IP_CACHE_DIR}

kerPack_gemm_Opt3_large_hw.xclbin: $(ker_gemm_Opt3_large_XOS) $(CONNECTIVITY_NAME_LARGE)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_LARGE) -o $@ $(ker_gemm_Opt3_large_XOS) --remote_ip_cache ${IP_CACHE_DIR}

kerPack_gemm_Opt3_extralarge_hw.xclbin: $(ker_gemm_Opt3_extralarge_XOS) $(CONNECTIVITY_NAME_EXTRALARGE)
	v++ -l $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_EXTRALARGE) -o $@ $(ker_gemm_Opt3_extralarge_XOS) --remote_ip_cache ${IP_CACHE_DIR}




ker_gemm_Opt3_mini.xo: $(ker_gemm_Opt3_SRC) $(ker_gemm_Opt3_HEADER)
	v++ --kernel $(ker_gemm_Opt3_mini_KERNEL) $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_MINI) $(ker_gemm_Opt3_mini_CUSTOMPARAMS) -c -o $@ $(ker_gemm_Opt3_SRC) $<

ker_gemm_Opt3_small.xo: $(ker_gemm_Opt3_SRC) $(ker_gemm_Opt3_HEADER)
	v++ --kernel $(ker_gemm_Opt3_small_KERNEL) $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_SMALL) $(ker_gemm_Opt3_small_CUSTOMPARAMS) -c -o $@ $(ker_gemm_Opt3_SRC) $<

ker_gemm_Opt3_medium.xo: $(ker_gemm_Opt3_SRC) $(ker_gemm_Opt3_HEADER)
	v++ --kernel $(ker_gemm_Opt3_medium_KERNEL) $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_MEDIUM) $(ker_gemm_Opt3_medium_CUSTOMPARAMS) -c -o $@ $(ker_gemm_Opt3_SRC) $<

ker_gemm_Opt3_large.xo: $(ker_gemm_Opt3_SRC) $(ker_gemm_Opt3_HEADER)
	v++ --kernel $(ker_gemm_Opt3_large_KERNEL) $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_LARGE) $(ker_gemm_Opt3_large_CUSTOMPARAMS) -c -o $@ $(ker_gemm_Opt3_SRC) $<

ker_gemm_Opt3_extralarge.xo: $(ker_gemm_Opt3_SRC) $(ker_gemm_Opt3_HEADER)
	v++ --kernel $(ker_gemm_Opt3_extralarge_KERNEL) $(VPPFLAGS_GENERAL) $(VPPLFLAGS_SPECIFIC_EXTRALARGE) $(ker_gemm_Opt3_extralarge_CUSTOMPARAMS) -c -o $@ $(ker_gemm_Opt3_SRC) $<
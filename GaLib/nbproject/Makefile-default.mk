#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=a
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/GaLib.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=a
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/GaLib.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/ai/ai.c src/ai/ai_actuator.c src/ai/ai_fresco.c src/ai/ai_mammooth.c src/control/controller.c src/control/encoders.c src/control/motors.c src/control/pid.c src/debug/leds.c src/debug/log.c src/io/adc.c src/io/bus.c src/io/config_flash.c src/io/dynamixel.c src/io/dxl_hal.c src/io/rtsp.s src/io/pwm.c src/tools/bits.c src/tools/timeout.c src/tracking/tracker.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/ai/ai.o ${OBJECTDIR}/src/ai/ai_actuator.o ${OBJECTDIR}/src/ai/ai_fresco.o ${OBJECTDIR}/src/ai/ai_mammooth.o ${OBJECTDIR}/src/control/controller.o ${OBJECTDIR}/src/control/encoders.o ${OBJECTDIR}/src/control/motors.o ${OBJECTDIR}/src/control/pid.o ${OBJECTDIR}/src/debug/leds.o ${OBJECTDIR}/src/debug/log.o ${OBJECTDIR}/src/io/adc.o ${OBJECTDIR}/src/io/bus.o ${OBJECTDIR}/src/io/config_flash.o ${OBJECTDIR}/src/io/dynamixel.o ${OBJECTDIR}/src/io/dxl_hal.o ${OBJECTDIR}/src/io/rtsp.o ${OBJECTDIR}/src/io/pwm.o ${OBJECTDIR}/src/tools/bits.o ${OBJECTDIR}/src/tools/timeout.o ${OBJECTDIR}/src/tracking/tracker.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/ai/ai.o.d ${OBJECTDIR}/src/ai/ai_actuator.o.d ${OBJECTDIR}/src/ai/ai_fresco.o.d ${OBJECTDIR}/src/ai/ai_mammooth.o.d ${OBJECTDIR}/src/control/controller.o.d ${OBJECTDIR}/src/control/encoders.o.d ${OBJECTDIR}/src/control/motors.o.d ${OBJECTDIR}/src/control/pid.o.d ${OBJECTDIR}/src/debug/leds.o.d ${OBJECTDIR}/src/debug/log.o.d ${OBJECTDIR}/src/io/adc.o.d ${OBJECTDIR}/src/io/bus.o.d ${OBJECTDIR}/src/io/config_flash.o.d ${OBJECTDIR}/src/io/dynamixel.o.d ${OBJECTDIR}/src/io/dxl_hal.o.d ${OBJECTDIR}/src/io/rtsp.o.d ${OBJECTDIR}/src/io/pwm.o.d ${OBJECTDIR}/src/tools/bits.o.d ${OBJECTDIR}/src/tools/timeout.o.d ${OBJECTDIR}/src/tracking/tracker.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/ai/ai.o ${OBJECTDIR}/src/ai/ai_actuator.o ${OBJECTDIR}/src/ai/ai_fresco.o ${OBJECTDIR}/src/ai/ai_mammooth.o ${OBJECTDIR}/src/control/controller.o ${OBJECTDIR}/src/control/encoders.o ${OBJECTDIR}/src/control/motors.o ${OBJECTDIR}/src/control/pid.o ${OBJECTDIR}/src/debug/leds.o ${OBJECTDIR}/src/debug/log.o ${OBJECTDIR}/src/io/adc.o ${OBJECTDIR}/src/io/bus.o ${OBJECTDIR}/src/io/config_flash.o ${OBJECTDIR}/src/io/dynamixel.o ${OBJECTDIR}/src/io/dxl_hal.o ${OBJECTDIR}/src/io/rtsp.o ${OBJECTDIR}/src/io/pwm.o ${OBJECTDIR}/src/tools/bits.o ${OBJECTDIR}/src/tools/timeout.o ${OBJECTDIR}/src/tracking/tracker.o

# Source Files
SOURCEFILES=src/ai/ai.c src/ai/ai_actuator.c src/ai/ai_fresco.c src/ai/ai_mammooth.c src/control/controller.c src/control/encoders.c src/control/motors.c src/control/pid.c src/debug/leds.c src/debug/log.c src/io/adc.c src/io/bus.c src/io/config_flash.c src/io/dynamixel.c src/io/dxl_hal.c src/io/rtsp.s src/io/pwm.c src/tools/bits.c src/tools/timeout.c src/tracking/tracker.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/GaLib.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512MU810
MP_LINKER_FILE_OPTION=,--script=p33EP512MU810.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/ai/ai.o: src/ai/ai.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ai 
	@${RM} ${OBJECTDIR}/src/ai/ai.o.d 
	@${RM} ${OBJECTDIR}/src/ai/ai.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ai/ai.c  -o ${OBJECTDIR}/src/ai/ai.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ai/ai.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/ai/ai.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ai/ai_actuator.o: src/ai/ai_actuator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ai 
	@${RM} ${OBJECTDIR}/src/ai/ai_actuator.o.d 
	@${RM} ${OBJECTDIR}/src/ai/ai_actuator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ai/ai_actuator.c  -o ${OBJECTDIR}/src/ai/ai_actuator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ai/ai_actuator.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/ai/ai_actuator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ai/ai_fresco.o: src/ai/ai_fresco.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ai 
	@${RM} ${OBJECTDIR}/src/ai/ai_fresco.o.d 
	@${RM} ${OBJECTDIR}/src/ai/ai_fresco.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ai/ai_fresco.c  -o ${OBJECTDIR}/src/ai/ai_fresco.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ai/ai_fresco.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/ai/ai_fresco.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ai/ai_mammooth.o: src/ai/ai_mammooth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ai 
	@${RM} ${OBJECTDIR}/src/ai/ai_mammooth.o.d 
	@${RM} ${OBJECTDIR}/src/ai/ai_mammooth.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ai/ai_mammooth.c  -o ${OBJECTDIR}/src/ai/ai_mammooth.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ai/ai_mammooth.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/ai/ai_mammooth.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/control/controller.o: src/control/controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/control 
	@${RM} ${OBJECTDIR}/src/control/controller.o.d 
	@${RM} ${OBJECTDIR}/src/control/controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/control/controller.c  -o ${OBJECTDIR}/src/control/controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/control/controller.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/control/controller.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/control/encoders.o: src/control/encoders.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/control 
	@${RM} ${OBJECTDIR}/src/control/encoders.o.d 
	@${RM} ${OBJECTDIR}/src/control/encoders.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/control/encoders.c  -o ${OBJECTDIR}/src/control/encoders.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/control/encoders.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/control/encoders.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/control/motors.o: src/control/motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/control 
	@${RM} ${OBJECTDIR}/src/control/motors.o.d 
	@${RM} ${OBJECTDIR}/src/control/motors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/control/motors.c  -o ${OBJECTDIR}/src/control/motors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/control/motors.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/control/motors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/control/pid.o: src/control/pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/control 
	@${RM} ${OBJECTDIR}/src/control/pid.o.d 
	@${RM} ${OBJECTDIR}/src/control/pid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/control/pid.c  -o ${OBJECTDIR}/src/control/pid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/control/pid.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/control/pid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/debug/leds.o: src/debug/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/debug 
	@${RM} ${OBJECTDIR}/src/debug/leds.o.d 
	@${RM} ${OBJECTDIR}/src/debug/leds.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/debug/leds.c  -o ${OBJECTDIR}/src/debug/leds.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/debug/leds.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/debug/leds.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/debug/log.o: src/debug/log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/debug 
	@${RM} ${OBJECTDIR}/src/debug/log.o.d 
	@${RM} ${OBJECTDIR}/src/debug/log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/debug/log.c  -o ${OBJECTDIR}/src/debug/log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/debug/log.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/debug/log.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/io/adc.o: src/io/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/adc.o.d 
	@${RM} ${OBJECTDIR}/src/io/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/io/adc.c  -o ${OBJECTDIR}/src/io/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/io/adc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/io/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/io/bus.o: src/io/bus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/bus.o.d 
	@${RM} ${OBJECTDIR}/src/io/bus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/io/bus.c  -o ${OBJECTDIR}/src/io/bus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/io/bus.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/io/bus.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/io/config_flash.o: src/io/config_flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/config_flash.o.d 
	@${RM} ${OBJECTDIR}/src/io/config_flash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/io/config_flash.c  -o ${OBJECTDIR}/src/io/config_flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/io/config_flash.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/io/config_flash.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/io/dynamixel.o: src/io/dynamixel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/dynamixel.o.d 
	@${RM} ${OBJECTDIR}/src/io/dynamixel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/io/dynamixel.c  -o ${OBJECTDIR}/src/io/dynamixel.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/io/dynamixel.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/io/dynamixel.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/io/dxl_hal.o: src/io/dxl_hal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/dxl_hal.o.d 
	@${RM} ${OBJECTDIR}/src/io/dxl_hal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/io/dxl_hal.c  -o ${OBJECTDIR}/src/io/dxl_hal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/io/dxl_hal.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/io/dxl_hal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/io/pwm.o: src/io/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/pwm.o.d 
	@${RM} ${OBJECTDIR}/src/io/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/io/pwm.c  -o ${OBJECTDIR}/src/io/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/io/pwm.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/io/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tools/bits.o: src/tools/bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/tools 
	@${RM} ${OBJECTDIR}/src/tools/bits.o.d 
	@${RM} ${OBJECTDIR}/src/tools/bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tools/bits.c  -o ${OBJECTDIR}/src/tools/bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tools/bits.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/tools/bits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tools/timeout.o: src/tools/timeout.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/tools 
	@${RM} ${OBJECTDIR}/src/tools/timeout.o.d 
	@${RM} ${OBJECTDIR}/src/tools/timeout.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tools/timeout.c  -o ${OBJECTDIR}/src/tools/timeout.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tools/timeout.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/tools/timeout.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tracking/tracker.o: src/tracking/tracker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/tracking 
	@${RM} ${OBJECTDIR}/src/tracking/tracker.o.d 
	@${RM} ${OBJECTDIR}/src/tracking/tracker.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tracking/tracker.c  -o ${OBJECTDIR}/src/tracking/tracker.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tracking/tracker.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/tracking/tracker.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/src/ai/ai.o: src/ai/ai.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ai 
	@${RM} ${OBJECTDIR}/src/ai/ai.o.d 
	@${RM} ${OBJECTDIR}/src/ai/ai.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ai/ai.c  -o ${OBJECTDIR}/src/ai/ai.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ai/ai.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/ai/ai.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ai/ai_actuator.o: src/ai/ai_actuator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ai 
	@${RM} ${OBJECTDIR}/src/ai/ai_actuator.o.d 
	@${RM} ${OBJECTDIR}/src/ai/ai_actuator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ai/ai_actuator.c  -o ${OBJECTDIR}/src/ai/ai_actuator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ai/ai_actuator.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/ai/ai_actuator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ai/ai_fresco.o: src/ai/ai_fresco.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ai 
	@${RM} ${OBJECTDIR}/src/ai/ai_fresco.o.d 
	@${RM} ${OBJECTDIR}/src/ai/ai_fresco.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ai/ai_fresco.c  -o ${OBJECTDIR}/src/ai/ai_fresco.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ai/ai_fresco.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/ai/ai_fresco.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ai/ai_mammooth.o: src/ai/ai_mammooth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ai 
	@${RM} ${OBJECTDIR}/src/ai/ai_mammooth.o.d 
	@${RM} ${OBJECTDIR}/src/ai/ai_mammooth.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ai/ai_mammooth.c  -o ${OBJECTDIR}/src/ai/ai_mammooth.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ai/ai_mammooth.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/ai/ai_mammooth.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/control/controller.o: src/control/controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/control 
	@${RM} ${OBJECTDIR}/src/control/controller.o.d 
	@${RM} ${OBJECTDIR}/src/control/controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/control/controller.c  -o ${OBJECTDIR}/src/control/controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/control/controller.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/control/controller.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/control/encoders.o: src/control/encoders.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/control 
	@${RM} ${OBJECTDIR}/src/control/encoders.o.d 
	@${RM} ${OBJECTDIR}/src/control/encoders.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/control/encoders.c  -o ${OBJECTDIR}/src/control/encoders.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/control/encoders.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/control/encoders.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/control/motors.o: src/control/motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/control 
	@${RM} ${OBJECTDIR}/src/control/motors.o.d 
	@${RM} ${OBJECTDIR}/src/control/motors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/control/motors.c  -o ${OBJECTDIR}/src/control/motors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/control/motors.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/control/motors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/control/pid.o: src/control/pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/control 
	@${RM} ${OBJECTDIR}/src/control/pid.o.d 
	@${RM} ${OBJECTDIR}/src/control/pid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/control/pid.c  -o ${OBJECTDIR}/src/control/pid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/control/pid.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/control/pid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/debug/leds.o: src/debug/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/debug 
	@${RM} ${OBJECTDIR}/src/debug/leds.o.d 
	@${RM} ${OBJECTDIR}/src/debug/leds.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/debug/leds.c  -o ${OBJECTDIR}/src/debug/leds.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/debug/leds.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/debug/leds.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/debug/log.o: src/debug/log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/debug 
	@${RM} ${OBJECTDIR}/src/debug/log.o.d 
	@${RM} ${OBJECTDIR}/src/debug/log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/debug/log.c  -o ${OBJECTDIR}/src/debug/log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/debug/log.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/debug/log.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/io/adc.o: src/io/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/adc.o.d 
	@${RM} ${OBJECTDIR}/src/io/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/io/adc.c  -o ${OBJECTDIR}/src/io/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/io/adc.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/io/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/io/bus.o: src/io/bus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/bus.o.d 
	@${RM} ${OBJECTDIR}/src/io/bus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/io/bus.c  -o ${OBJECTDIR}/src/io/bus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/io/bus.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/io/bus.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/io/config_flash.o: src/io/config_flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/config_flash.o.d 
	@${RM} ${OBJECTDIR}/src/io/config_flash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/io/config_flash.c  -o ${OBJECTDIR}/src/io/config_flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/io/config_flash.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/io/config_flash.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/io/dynamixel.o: src/io/dynamixel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/dynamixel.o.d 
	@${RM} ${OBJECTDIR}/src/io/dynamixel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/io/dynamixel.c  -o ${OBJECTDIR}/src/io/dynamixel.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/io/dynamixel.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/io/dynamixel.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/io/dxl_hal.o: src/io/dxl_hal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/dxl_hal.o.d 
	@${RM} ${OBJECTDIR}/src/io/dxl_hal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/io/dxl_hal.c  -o ${OBJECTDIR}/src/io/dxl_hal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/io/dxl_hal.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/io/dxl_hal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/io/pwm.o: src/io/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/pwm.o.d 
	@${RM} ${OBJECTDIR}/src/io/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/io/pwm.c  -o ${OBJECTDIR}/src/io/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/io/pwm.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/io/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tools/bits.o: src/tools/bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/tools 
	@${RM} ${OBJECTDIR}/src/tools/bits.o.d 
	@${RM} ${OBJECTDIR}/src/tools/bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tools/bits.c  -o ${OBJECTDIR}/src/tools/bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tools/bits.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/tools/bits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tools/timeout.o: src/tools/timeout.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/tools 
	@${RM} ${OBJECTDIR}/src/tools/timeout.o.d 
	@${RM} ${OBJECTDIR}/src/tools/timeout.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tools/timeout.c  -o ${OBJECTDIR}/src/tools/timeout.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tools/timeout.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/tools/timeout.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tracking/tracker.o: src/tracking/tracker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/tracking 
	@${RM} ${OBJECTDIR}/src/tracking/tracker.o.d 
	@${RM} ${OBJECTDIR}/src/tracking/tracker.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tracking/tracker.c  -o ${OBJECTDIR}/src/tracking/tracker.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tracking/tracker.o.d"      -mno-eds-warn  -g -omf=elf -fast-math -O0 -I"include" -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/tracking/tracker.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/io/rtsp.o: src/io/rtsp.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/rtsp.o.d 
	@${RM} ${OBJECTDIR}/src/io/rtsp.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/io/rtsp.s  -o ${OBJECTDIR}/src/io/rtsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -fast-math -Wa,-MD,"${OBJECTDIR}/src/io/rtsp.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/io/rtsp.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/io/rtsp.o: src/io/rtsp.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/io 
	@${RM} ${OBJECTDIR}/src/io/rtsp.o.d 
	@${RM} ${OBJECTDIR}/src/io/rtsp.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/io/rtsp.s  -o ${OBJECTDIR}/src/io/rtsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -fast-math -Wa,-MD,"${OBJECTDIR}/src/io/rtsp.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/io/rtsp.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: archive
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/GaLib.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/GaLib.${OUTPUT_SUFFIX} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  -omf=elf -r dist/${CND_CONF}/${IMAGE_TYPE}/GaLib.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/GaLib.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/GaLib.${OUTPUT_SUFFIX} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  -omf=elf -r dist/${CND_CONF}/${IMAGE_TYPE}/GaLib.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif

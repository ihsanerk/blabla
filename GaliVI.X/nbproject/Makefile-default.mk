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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/GaliVI.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/GaliVI.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Ascenseur.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/AscenseurListe.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Asservissement.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/AsservissementListe.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/AX12.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Balise.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Bras.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/CommunicationBaby.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Debugger.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Definitions.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/DetectionSharp.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/DetectionTourelle.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/IA.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/IAListe.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Main.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Moteur.c" "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Uart.c"

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/766965082/Ascenseur.o ${OBJECTDIR}/_ext/766965082/AscenseurListe.o ${OBJECTDIR}/_ext/766965082/Asservissement.o ${OBJECTDIR}/_ext/766965082/AsservissementListe.o ${OBJECTDIR}/_ext/766965082/AX12.o ${OBJECTDIR}/_ext/766965082/Balise.o ${OBJECTDIR}/_ext/766965082/Bras.o ${OBJECTDIR}/_ext/766965082/CommunicationBaby.o ${OBJECTDIR}/_ext/766965082/Debugger.o ${OBJECTDIR}/_ext/766965082/Definitions.o ${OBJECTDIR}/_ext/766965082/DetectionSharp.o ${OBJECTDIR}/_ext/766965082/DetectionTourelle.o ${OBJECTDIR}/_ext/766965082/IA.o ${OBJECTDIR}/_ext/766965082/IAListe.o ${OBJECTDIR}/_ext/766965082/Main.o ${OBJECTDIR}/_ext/766965082/Moteur.o ${OBJECTDIR}/_ext/766965082/Uart.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/766965082/Ascenseur.o.d ${OBJECTDIR}/_ext/766965082/AscenseurListe.o.d ${OBJECTDIR}/_ext/766965082/Asservissement.o.d ${OBJECTDIR}/_ext/766965082/AsservissementListe.o.d ${OBJECTDIR}/_ext/766965082/AX12.o.d ${OBJECTDIR}/_ext/766965082/Balise.o.d ${OBJECTDIR}/_ext/766965082/Bras.o.d ${OBJECTDIR}/_ext/766965082/CommunicationBaby.o.d ${OBJECTDIR}/_ext/766965082/Debugger.o.d ${OBJECTDIR}/_ext/766965082/Definitions.o.d ${OBJECTDIR}/_ext/766965082/DetectionSharp.o.d ${OBJECTDIR}/_ext/766965082/DetectionTourelle.o.d ${OBJECTDIR}/_ext/766965082/IA.o.d ${OBJECTDIR}/_ext/766965082/IAListe.o.d ${OBJECTDIR}/_ext/766965082/Main.o.d ${OBJECTDIR}/_ext/766965082/Moteur.o.d ${OBJECTDIR}/_ext/766965082/Uart.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/766965082/Ascenseur.o ${OBJECTDIR}/_ext/766965082/AscenseurListe.o ${OBJECTDIR}/_ext/766965082/Asservissement.o ${OBJECTDIR}/_ext/766965082/AsservissementListe.o ${OBJECTDIR}/_ext/766965082/AX12.o ${OBJECTDIR}/_ext/766965082/Balise.o ${OBJECTDIR}/_ext/766965082/Bras.o ${OBJECTDIR}/_ext/766965082/CommunicationBaby.o ${OBJECTDIR}/_ext/766965082/Debugger.o ${OBJECTDIR}/_ext/766965082/Definitions.o ${OBJECTDIR}/_ext/766965082/DetectionSharp.o ${OBJECTDIR}/_ext/766965082/DetectionTourelle.o ${OBJECTDIR}/_ext/766965082/IA.o ${OBJECTDIR}/_ext/766965082/IAListe.o ${OBJECTDIR}/_ext/766965082/Main.o ${OBJECTDIR}/_ext/766965082/Moteur.o ${OBJECTDIR}/_ext/766965082/Uart.o

# Source Files
SOURCEFILES=../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Ascenseur.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/AscenseurListe.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Asservissement.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/AsservissementListe.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/AX12.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Balise.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Bras.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/CommunicationBaby.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Debugger.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Definitions.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/DetectionSharp.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/DetectionTourelle.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/IA.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/IAListe.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Main.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Moteur.c ../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Uart.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/GaliVI.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512MU810
MP_LINKER_FILE_OPTION=,--script=p33EP512MU810.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/766965082/Ascenseur.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Ascenseur.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Ascenseur.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Ascenseur.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Ascenseur.c"  -o ${OBJECTDIR}/_ext/766965082/Ascenseur.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Ascenseur.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Ascenseur.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/AscenseurListe.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/AscenseurListe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/AscenseurListe.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/AscenseurListe.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/AscenseurListe.c"  -o ${OBJECTDIR}/_ext/766965082/AscenseurListe.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/AscenseurListe.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/AscenseurListe.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Asservissement.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Asservissement.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Asservissement.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Asservissement.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Asservissement.c"  -o ${OBJECTDIR}/_ext/766965082/Asservissement.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Asservissement.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Asservissement.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/AsservissementListe.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/AsservissementListe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/AsservissementListe.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/AsservissementListe.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/AsservissementListe.c"  -o ${OBJECTDIR}/_ext/766965082/AsservissementListe.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/AsservissementListe.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/AsservissementListe.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/AX12.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/AX12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/AX12.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/AX12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/AX12.c"  -o ${OBJECTDIR}/_ext/766965082/AX12.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/AX12.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/AX12.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Balise.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Balise.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Balise.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Balise.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Balise.c"  -o ${OBJECTDIR}/_ext/766965082/Balise.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Balise.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Balise.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Bras.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Bras.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Bras.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Bras.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Bras.c"  -o ${OBJECTDIR}/_ext/766965082/Bras.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Bras.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Bras.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/CommunicationBaby.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/CommunicationBaby.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/CommunicationBaby.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/CommunicationBaby.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/CommunicationBaby.c"  -o ${OBJECTDIR}/_ext/766965082/CommunicationBaby.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/CommunicationBaby.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/CommunicationBaby.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Debugger.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Debugger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Debugger.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Debugger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Debugger.c"  -o ${OBJECTDIR}/_ext/766965082/Debugger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Debugger.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Debugger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Definitions.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Definitions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Definitions.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Definitions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Definitions.c"  -o ${OBJECTDIR}/_ext/766965082/Definitions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Definitions.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Definitions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/DetectionSharp.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/DetectionSharp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/DetectionSharp.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/DetectionSharp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/DetectionSharp.c"  -o ${OBJECTDIR}/_ext/766965082/DetectionSharp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/DetectionSharp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/DetectionSharp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/DetectionTourelle.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/DetectionTourelle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/DetectionTourelle.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/DetectionTourelle.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/DetectionTourelle.c"  -o ${OBJECTDIR}/_ext/766965082/DetectionTourelle.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/DetectionTourelle.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/DetectionTourelle.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/IA.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/IA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/IA.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/IA.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/IA.c"  -o ${OBJECTDIR}/_ext/766965082/IA.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/IA.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/IA.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/IAListe.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/IAListe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/IAListe.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/IAListe.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/IAListe.c"  -o ${OBJECTDIR}/_ext/766965082/IAListe.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/IAListe.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/IAListe.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Main.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Main.c"  -o ${OBJECTDIR}/_ext/766965082/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Moteur.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Moteur.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Moteur.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Moteur.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Moteur.c"  -o ${OBJECTDIR}/_ext/766965082/Moteur.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Moteur.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Moteur.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Uart.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Uart.c"  -o ${OBJECTDIR}/_ext/766965082/Uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/766965082/Ascenseur.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Ascenseur.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Ascenseur.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Ascenseur.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Ascenseur.c"  -o ${OBJECTDIR}/_ext/766965082/Ascenseur.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Ascenseur.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Ascenseur.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/AscenseurListe.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/AscenseurListe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/AscenseurListe.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/AscenseurListe.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/AscenseurListe.c"  -o ${OBJECTDIR}/_ext/766965082/AscenseurListe.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/AscenseurListe.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/AscenseurListe.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Asservissement.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Asservissement.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Asservissement.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Asservissement.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Asservissement.c"  -o ${OBJECTDIR}/_ext/766965082/Asservissement.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Asservissement.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Asservissement.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/AsservissementListe.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/AsservissementListe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/AsservissementListe.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/AsservissementListe.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/AsservissementListe.c"  -o ${OBJECTDIR}/_ext/766965082/AsservissementListe.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/AsservissementListe.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/AsservissementListe.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/AX12.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/AX12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/AX12.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/AX12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/AX12.c"  -o ${OBJECTDIR}/_ext/766965082/AX12.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/AX12.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/AX12.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Balise.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Balise.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Balise.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Balise.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Balise.c"  -o ${OBJECTDIR}/_ext/766965082/Balise.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Balise.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Balise.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Bras.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Bras.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Bras.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Bras.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Bras.c"  -o ${OBJECTDIR}/_ext/766965082/Bras.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Bras.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Bras.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/CommunicationBaby.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/CommunicationBaby.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/CommunicationBaby.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/CommunicationBaby.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/CommunicationBaby.c"  -o ${OBJECTDIR}/_ext/766965082/CommunicationBaby.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/CommunicationBaby.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/CommunicationBaby.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Debugger.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Debugger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Debugger.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Debugger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Debugger.c"  -o ${OBJECTDIR}/_ext/766965082/Debugger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Debugger.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Debugger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Definitions.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Definitions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Definitions.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Definitions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Definitions.c"  -o ${OBJECTDIR}/_ext/766965082/Definitions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Definitions.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Definitions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/DetectionSharp.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/DetectionSharp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/DetectionSharp.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/DetectionSharp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/DetectionSharp.c"  -o ${OBJECTDIR}/_ext/766965082/DetectionSharp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/DetectionSharp.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/DetectionSharp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/DetectionTourelle.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/DetectionTourelle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/DetectionTourelle.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/DetectionTourelle.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/DetectionTourelle.c"  -o ${OBJECTDIR}/_ext/766965082/DetectionTourelle.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/DetectionTourelle.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/DetectionTourelle.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/IA.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/IA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/IA.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/IA.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/IA.c"  -o ${OBJECTDIR}/_ext/766965082/IA.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/IA.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/IA.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/IAListe.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/IAListe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/IAListe.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/IAListe.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/IAListe.c"  -o ${OBJECTDIR}/_ext/766965082/IAListe.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/IAListe.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/IAListe.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Main.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Main.c"  -o ${OBJECTDIR}/_ext/766965082/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Main.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Moteur.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Moteur.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Moteur.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Moteur.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Moteur.c"  -o ${OBJECTDIR}/_ext/766965082/Moteur.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Moteur.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Moteur.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/766965082/Uart.o: ../../../Desktop/Test/GaliVI_vf/Projet\ Gali\ VI/Gali\ VI/Uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/766965082 
	@${RM} ${OBJECTDIR}/_ext/766965082/Uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/766965082/Uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../Desktop/Test/GaliVI_vf/Projet Gali VI/Gali VI/Uart.c"  -o ${OBJECTDIR}/_ext/766965082/Uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/766965082/Uart.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/766965082/Uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/GaliVI.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/GaliVI.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf  -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/GaliVI.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/GaliVI.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/GaliVI.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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

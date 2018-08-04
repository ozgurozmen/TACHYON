##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Tachyon
ConfigurationName      :=Debug
WorkspacePath          :=/media/ozgur/Ubuntu/MyGit/TACHYON/Tachyon
ProjectPath            :=/media/ozgur/Ubuntu/MyGit/TACHYON/Tachyon/Tachyon
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Ozgur Ozmen
Date                   :=04/08/18
CodeLitePath           :=/home/ozgur/.codelite
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Tachyon.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lb2   -lm
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)usr/local/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O3 -Wall $(Preprocessors)
CFLAGS   :=  -g -O3 -Wall -march=native $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/aes.c$(ObjectSuffix) $(IntermediateDirectory)/ntt.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/ozgur/Ubuntu/MyGit/TACHYON/Tachyon/Tachyon/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/aes.c$(ObjectSuffix): aes.c $(IntermediateDirectory)/aes.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/ozgur/Ubuntu/MyGit/TACHYON/Tachyon/Tachyon/aes.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/aes.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aes.c$(DependSuffix): aes.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/aes.c$(ObjectSuffix) -MF$(IntermediateDirectory)/aes.c$(DependSuffix) -MM aes.c

$(IntermediateDirectory)/aes.c$(PreprocessSuffix): aes.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aes.c$(PreprocessSuffix) aes.c

$(IntermediateDirectory)/ntt.c$(ObjectSuffix): ntt.c $(IntermediateDirectory)/ntt.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/ozgur/Ubuntu/MyGit/TACHYON/Tachyon/Tachyon/ntt.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ntt.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ntt.c$(DependSuffix): ntt.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ntt.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ntt.c$(DependSuffix) -MM ntt.c

$(IntermediateDirectory)/ntt.c$(PreprocessSuffix): ntt.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ntt.c$(PreprocessSuffix) ntt.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/



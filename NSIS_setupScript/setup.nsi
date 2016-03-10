; using nsis 

; some defines
!define PRODUCT_NAME "your Product name"
!define PRODUCT_VERSION "your product version"
!define PRODUCT_PUBLISHER "your name"
!define PRODUCT_WEB_SITE "your web site"
!define PRODUCT_INST_KEY "Software\Microsoft\Windows\CurrentVersion\install\${PRODUCT_NAME}"
!define PRODUCT_INST_ROOT_KEY "HKLM"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

!define APP_NAME "your app name"
!define COMPANY_NAME "your company name"



SetCompressor lzma

; ------ MUI (1.67) ------
!include "MUI.nsh"
!include "Library.nsh"
!include "WordFunc.nsh"
!include "WinMessages.nsh"
!include "nsProcess.nsh" ; <---- require nsis plugin

; MUI define
!define MUI_ABORTWARNING
!define MUI_ICON "${APP_NAME}.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"
!define LIBRARY_X64

!ifdef LIBRARY_X64
	!define PROGRAM_FILES_MAP  $PROGRAMFILES64
!else
	!define PROGRAM_FILES_MAP  $PROGRAMFILES
!endif

; welcome MUI
!insertmacro MUI_PAGE_WELCOME
; directory page MUI 
!insertmacro MUI_PAGE_DIRECTORY
; install file progress page MUI
!insertmacro MUI_PAGE_INSTFILES
; finish page MUI
!insertmacro MUI_PAGE_FINISH

; uninstall page MUI
!insertmacro MUI_UNPAGE_INSTFILES

; MUI using language
!insertmacro MUI_LANGUAGE "SimpChinese"

; reserve file for install
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "..\ReleaseVersion\${APP_NAME}V${PRODUCT_VERSION}_Setup.exe"
InstallDir "${PROGRAM_FILES_MAP}\${COMPANY_NAME}\${APP_NAME}"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUninstDetails show



Var FindProcessResult
RequestExecutionLevel admin

Section APP_NAME SEC01
   SetShellVarContext all

   AddSize 500000

	!ifdef  LIBRARY_X64
 		${DisableX64FSRedirection}
	!endif
	
	; check app is runing ?
	Call IsYourAPPRun

	;copy some dlls or other file
  
  SetOverwrite on
  SetOutPath "$INSTDIR\${APP_NAME}"
  File /r "..\Release\*.*"
  CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}\${APP_NAME}.exe" "${MUI_ICON}"
  
  CreateDirectory "$SMPROGRAMS\${COMPANY_NAME}\${APP_NAME}"
  CreateShortCut "$SMPROGRAMS\${COMPANY_NAME}\${APP_NAME}\${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}\${APP_NAME}.exe" "${MUI_ICON}" 
  CreateShortCut "$SMPROGRAMS\${COMPANY_NAME}\${APP_NAME}\Uninstall.lnk" "$INSTDIR\Uninstall.exe" "${MUI_UNICON}" 
  
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  !ifdef LIBRARY_X64
 		SetRegView 64
	!endif

  ;write register
  WriteRegStr ${PRODUCT_INST_ROOT_KEY} "${PRODUCT_INST_KEY}" "installPath" "$INSTDIR\${APP_NAME}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\Uninstall.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  
	;end register option
	
  !ifdef LIBRARY_X64
 		SetRegView lastused
	!endif
SectionEnd

/******************************
 *  uninstall progress  *
 ******************************/

Section Uninstall

    SetShellVarContext all

	Call un.IsYourAPPRun

  RMDir /r /REBOOTOK "$INSTDIR\${APP_NAME}"

  !ifdef LIBRARY_X64
 		SetRegView 64
	!endif
	
	;delete register
  DeleteRegKey ${PRODUCT_INST_ROOT_KEY} "${PRODUCT_INST_KEY}"
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  ;DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  ; end register 

  !ifdef LIBRARY_X64
 		SetRegView lastused
	!endif
  
  Delete /REBOOTOK "$DESKTOP\${APP_NAME}.lnk"
  Delete /REBOOTOK "$SMPROGRAMS\${COMPANY_NAME}\${APP_NAME}\${APP_NAME}.lnk"
  Delete /REBOOTOK "$SMPROGRAMS\${COMPANY_NAME}\${APP_NAME}\Uninstall.lnk"
  RMDir /r /REBOOTOK "$SMPROGRAMS\${COMPANY_NAME}\${APP_NAME}"
  
  Delete /REBOOTOK "$INSTDIR\Uninstall.exe"
  RMDir /r /REBOOTOK "$INSTDIR"
    
  SetAutoClose true
SectionEnd

#-- some function at here --#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "您确实要完全移除 $(^Name) ，及其所有的组件？" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从您的计算机移除。"
FunctionEnd


;-- check win64 platform --#
Function IsWIN64
	${If} ${RunningX64}
	
	${Else}
		; it is not win64 platform
		MessageBox MB_OK "不能安装到非64位操作系统中。"
    Quit
	${EndIf}
FunctionEnd

Function .onInit
	call IsWIN64
FunctionEnd


;-- check your app is running to install --#
Function IsYourAPPRun
	nsProcess::_FindProcess /NOUNLOAD "${APP_NAME}.exe"
	Pop $FindProcessResult
	${If} $FindProcessResult == 0
	 MessageBox MB_ICONQUESTION|MB_OKCANCEL|MB_DEFBUTTON1 "检测到${APP_NAME}.exe正在运行，请退出${APP_NAME}}.exe后重试。\
			$\r$\n$\r$\n点击“确定”，立即结束${APP_NAME}.exe，然后继续进行安装；$\r$\n点击“取消”，退出安装。" IDCANCEL abort
	  	nsProcess::_KillProcess /NOUNLOAD "${APP_NAME}.exe"
	  	Sleep 3000
			Goto next
	  abort:
	    Quit
    next:
	${EndIf}
FunctionEnd

;-- check your app is running to uninstall --#
Function un.IsYourAPPRun
	nsProcess::_FindProcess /NOUNLOAD "${APP_NAME}.exe"
	Pop $FindProcessResult
	${If} $FindProcessResult == 0
	  MessageBox MB_ICONQUESTION|MB_OKCANCEL|MB_DEFBUTTON1 "检测到${APP_NAME}.exe正在运行，请退出${APP_NAME}.exe后重试。\
		$\r$\n$\r$\n点击“确定”，立即结束${APP_NAME}.exe，然后继续进行卸载；$\r$\n点击“取消”，退出卸载。" IDCANCEL abort
	  	nsProcess::_KillProcess /NOUNLOAD "${APP_NAME}.exe"
	  	Sleep 3000
			Goto next
	  abort:
	    Quit
    next:
	${EndIf}
FunctionEnd



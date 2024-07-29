; Include Modern UI 2
!include MUI2.nsh

; Define name
!define PROJECT_NAME_FULL   "Tic-Tac-Gone"
!define PROJECT_NAME_SHORT  "TicTacGone"
!define PUBLISHER_NAME_FULL "James Steele Seeley"
!define COPYRIGHT_YEAR      "2024"
!define PROJECT_ROOT        "..\..\..\"

; Define project version number
!define PROJECT_VERSION_SHORT "2.0"
!define PROJECT_VERSION_FULL  "2.0.0.0"

; Define installer version number
!define INSTALLER_VERSION "2.0.0.0"

!define INSTALLER_FILENAME "${PROJECT_NAME_SHORT}_${PROJECT_VERSION_SHORT}_Win64_Install.exe"

Name "${PROJECT_NAME_FULL} ${PROJECT_VERSION_SHORT}"
OutFile "${PROJECT_ROOT}Release/${INSTALLER_FILENAME}"

InstallDir "$PROGRAMFILES64\${PROJECT_NAME_FULL}"
InstallDirRegKey HKLM "Software\${PROJECT_NAME_SHORT}" "Install_Dir"

SetCompressor /SOLID lzma
XPStyle on

; MUI settings
!define MUI_ABORTWARNING
!define MUI_ICON   "${PROJECT_ROOT}Icon.ico"
!define MUI_UNICON "${PROJECT_ROOT}Icon.ico"

; Custom image for the installer
!define MUI_WELCOMEFINISHPAGE_BITMAP "T_Side.bmp"

; Welcome page
!insertmacro MUI_PAGE_WELCOME

; License page
!insertmacro MUI_PAGE_LICENSE "${PROJECT_ROOT}LICENSE.txt"

; Components page
!insertmacro MUI_PAGE_COMPONENTS

; Directory page
!insertmacro MUI_PAGE_DIRECTORY

; Instfiles page
!insertmacro MUI_PAGE_INSTFILES

; Finish page
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; Installer properties
VIProductVersion "${INSTALLER_VERSION}"
VIAddVersionKey /LANG=1033 "ProductName" "${PROJECT_NAME_FULL}"
VIAddVersionKey /LANG=1033 "FileDescription" "${PROJECT_NAME_FULL} Installer"
VIAddVersionKey /LANG=1033 "CompanyName" "${PUBLISHER_NAME_FULL}"
VIAddVersionKey /LANG=1033 "LegalCopyright" "(c) ${COPYRIGHT_YEAR} ${PUBLISHER_NAME_FULL}"
VIAddVersionKey /LANG=1033 "FileVersion" "${INSTALLER_VERSION}"
VIAddVersionKey /LANG=1033 "ProductVersion" "${PROJECT_VERSION_FULL}"
VIAddVersionKey /LANG=1033 "OriginalFilename" "${INSTALLER_FILENAME}"
VIAddVersionKey /LANG=1033 "InternalName" "${PROJECT_NAME_SHORT}_Installer"

Section "${PROJECT_NAME_FULL} (required)" SecMain
  SectionIn RO

  SetOutPath $INSTDIR

  File /r "${PROJECT_ROOT}x64\Release\*.*"
  File "${PROJECT_ROOT}LICENSE.txt"
  File "${PROJECT_ROOT}Icon.ico"

  WriteRegStr   HKLM "SOFTWARE\${PROJECT_NAME_SHORT}" "Install_Dir" "$INSTDIR"
  WriteRegStr   HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PROJECT_NAME_SHORT}" "DisplayName"     "${PROJECT_NAME_FULL}"
  WriteRegStr   HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PROJECT_NAME_SHORT}" "DisplayVersion"  "${PROJECT_VERSION_SHORT}"
  WriteRegStr   HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PROJECT_NAME_SHORT}" "Publisher"       "${PUBLISHER_NAME_FULL}"
  WriteRegStr   HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PROJECT_NAME_SHORT}" "UninstallString" '"$INSTDIR\Uninstall.exe"'
  WriteRegStr   HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PROJECT_NAME_SHORT}" "DisplayIcon"     "$INSTDIR\Icon.ico"
  WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PROJECT_NAME_SHORT}" "NoModify"        1
  WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PROJECT_NAME_SHORT}" "NoRepair"        1

  WriteUninstaller "uninstall.exe"
SectionEnd

Section "Start Menu Shortcuts" SecShortcutsStart
  CreateDirectory "$SMPROGRAMS\${PROJECT_NAME_FULL}"

  SetOutPath "$INSTDIR"

  ; Add the start menu shortcuts
  CreateShortCut "$SMPROGRAMS\${PROJECT_NAME_FULL}\${PROJECT_NAME_FULL}.lnk" "$INSTDIR\${PROJECT_NAME_SHORT}.exe" "" "$INSTDIR\${PROJECT_NAME_SHORT}.exe" 0
  CreateShortCut "$SMPROGRAMS\${PROJECT_NAME_FULL}\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
SectionEnd

Section "Desktop Shortcut" SecShortcutsDesktop
  CreateShortCut "$DESKTOP\${PROJECT_NAME_FULL}.lnk" "$INSTDIR\${PROJECT_NAME_SHORT}.exe" "" "$INSTDIR\${PROJECT_NAME_SHORT}.exe" 0
SectionEnd

; Component descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SecMain} "Main installation of ${PROJECT_NAME_FULL}"
  !insertmacro MUI_DESCRIPTION_TEXT ${SecShortcutsStart} "Create Start Menu shortcuts"
  !insertmacro MUI_DESCRIPTION_TEXT ${SecShortcutsDesktop} "Create Desktop shortcut"
!insertmacro MUI_FUNCTION_DESCRIPTION_END

Section "Uninstall"
  DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PROJECT_NAME_SHORT}"
  DeleteRegKey HKLM "SOFTWARE\${PROJECT_NAME_SHORT}"

  RMDir /r "$SMPROGRAMS\${PROJECT_NAME_FULL}"
  RMDir /r "$INSTDIR"
  Delete "$DESKTOP\${PROJECT_NAME_FULL}.lnk"
SectionEnd

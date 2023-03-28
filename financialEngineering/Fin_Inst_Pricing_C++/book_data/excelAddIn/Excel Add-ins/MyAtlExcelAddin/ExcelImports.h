// Import necessary typelib's for Excel

// Office 97
//#import "d:\program files\microsoft office\office\mso97.dll" no_namespace rename("DocumentProperties", "DocumentPropertiesXL") 
//#import "d:\program files\common files\microsoft shared\vba\vbeext1.olb" no_namespace 
//#import "d:\program files\microsoft office\office\Excel8.olb" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") no_dual_interfaces


// Office 2000
//#import "C:\Program Files\Microsoft Office\Office\mso9.dll" no_namespace rename("DocumentProperties", "DocumentPropertiesXL") 
//#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\vbe6ext.olb" no_namespace
//#import "C:\Program Files\Microsoft Office\Office\Excel9.olb" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") no_dual_interfaces

// Office XP (2002)
#import "C:\Program Files\Common Files\Microsoft Shared\office10\mso.dll" rename("DocumentProperties", "DocumentPropertiesXL") rename("RGB", "RBGXL")
#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\vbe6ext.olb"
#import "C:\Program Files\Microsoft Office\Office10\EXCEL.EXE" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") rename("ReplaceText", "ReplaceTextXL") rename("CopyFile", "CopyFileXL") no_dual_interfaces

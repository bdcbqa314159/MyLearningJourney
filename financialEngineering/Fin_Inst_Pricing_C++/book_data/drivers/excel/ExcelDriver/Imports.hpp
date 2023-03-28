// Import necessary typelib's for Excel

// Office 97
//#import "d:\program files\microsoft office\office\mso97.dll" no_namespace rename("DocumentProperties", "DocumentPropertiesXL") no_implementation
//#import "d:\program files\common files\microsoft shared\vba\vbeext1.olb" no_namespace no_implementation
//#import "d:\program files\microsoft office\office\Excel8.olb" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") no_implementation no_dual_interfaces


// Office 2000
//#import "C:\Program Files\Microsoft Office\Office\mso9.dll" no_namespace rename("DocumentProperties", "DocumentPropertiesXL") no_implementation
//#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\vbe6ext.olb" no_namespace no_implementation
//#import "C:\Program Files\Microsoft Office\Office\Excel9.olb" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") no_implementation no_dual_interfaces

// Office 2000 - local typelibraries.
#import "TypeLibraries\mso9.dll" no_namespace rename("DocumentProperties", "DocumentPropertiesXL") no_implementation
#import "TypeLibraries\vbe6ext.olb" no_namespace rename("Property", "PropertyVB") no_implementation
#import "TypeLibraries\Excel9.olb" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") no_implementation no_dual_interfaces
#include "imports.hpp"

// Office 97
//#import "d:\program files\microsoft office\office\mso97.dll" no_namespace rename("DocumentProperties", "DocumentPropertiesXL") implementation_only
//#import "d:\program files\common files\microsoft shared\vba\vbeext1.olb" no_namespace implementation_only
//#import "d:\program files\microsoft office\office\Excel8.olb" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") implementation_only no_dual_interfaces

// Office 2000
//#import "D:\Program Files\Microsoft Office\Office\mso9.dll" no_namespace rename("DocumentProperties", "DocumentPropertiesXL") implementation_only
//#import "D:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\vbe6ext.olb" no_namespace implementation_only
//#import "D:\Program Files\Microsoft Office\Office\Excel9.olb" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") implementation_only no_dual_interfaces

#import "TypeLibraries\mso9.dll" no_namespace rename("DocumentProperties", "DocumentPropertiesXL") implementation_only
#import "TypeLibraries\vbe6ext.olb" no_namespace rename("Property", "PropertyVB") implementation_only
#import "TypeLibraries\Excel9.olb" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") implementation_only no_dual_interfaces

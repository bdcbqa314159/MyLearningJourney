using System;
using Extensibility;
using Office=Microsoft.Office.Core;
using Excel=Microsoft.Office.Interop.Excel;

/// <summary>
/// Summary description for AddInUtils.
/// </summary>
public class AddInUtils
{
	// Add a menu item
	public static Office.CommandBarButton AddMenuItem(Excel.Application xl, Office.COMAddIn addin, string menuName, string menuItemCaption, string menuItemKey)
	{
		Office.CommandBar cmdBar;
		Office.CommandBarButton button;

		// Make variable for 'missing' arguments. This is not the same as null
		object missing=System.Reflection.Missing.Value;
    
		// Get the "menuName" dropdown menu
		cmdBar = xl.CommandBars[menuName];
    
		// If not found then end of exercition
		if (cmdBar==null) return null;
    
		// Try to get the "menuItemCaption" menu item
		button = cmdBar.FindControl(missing, missing, menuItemKey, missing, missing) as Office.CommandBarButton;
    
		// If not found, add it
		if (button==null)
		{
        
			// Add new button
			button = cmdBar.Controls.Add(Office.MsoControlType.msoControlButton, missing, menuItemKey, missing, missing) as Office.CommandBarButton;
        
			// Set button's Caption, Tag, Style, and OnAction properties.
			button.Caption = menuItemCaption;
			button.Tag = menuItemKey;
			button.Style = Office.MsoButtonStyle.msoButtonCaption;
            
			// Use addin argument to return reference to this add-in.
			button.OnAction = "!<" + addin.ProgId + ">";
		}

    
		// Return the created button
		return button;
	}


	// Remove the installed menu item
	public static void RemoveMenuItem(Excel.Application xl,  Extensibility.ext_DisconnectMode removeMode, string menuName, string menuItemCaption)
	{
		// Make variable for 'missing' arguments. This is not the same as null
		object missing=System.Reflection.Missing.Value;

		// If user unloaded add-in, remove button. Otherwise, add-in is
		// being unloaded because application is closing; in that case,
		// leave button as is.
		if (removeMode == Extensibility.ext_DisconnectMode.ext_dm_UserClosed)
		{
			// Delete custom command bar button.
			xl.CommandBars[menuName].Controls[menuItemCaption].Delete(missing);
		}
	}
}


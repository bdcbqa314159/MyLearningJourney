namespace MyDotNetAddin
{
	using System;
	using Office=Microsoft.Office.Core;
	using Excel=Microsoft.Office.Interop.Excel;
	using Extensibility;
	using System.Runtime.InteropServices;
	

	#region Read me for Add-in installation and setup information.
	// When run, the Add-in wizard prepared the registry for the Add-in.
	// At a later time, if the Add-in becomes unavailable for reasons such as:
	//   1) You moved this project to a computer other than which is was originally created on.
	//   2) You chose 'Yes' when presented with a message asking if you wish to remove the Add-in.
	//   3) Registry corruption.
	// you will need to re-register the Add-in by building the MyAddin21Setup project 
	// by right clicking the project in the Solution Explorer, then choosing install.
	#endregion
	
	public interface IMyFunctions
	{
		double MySubtract(double value1, double value2);
		double MyAdd(Excel.Range range);
	}

	/// <summary>
	///   The object for implementing an Add-in.
	/// </summary>
	/// <seealso class='IDTExtensibility2' />
	[GuidAttribute("ECB9B021-8CE5-4975-BEED-15964BC768D0")]
	[ProgId("MyDotNetAddin.Connect")]
	[ClassInterface(ClassInterfaceType.None)]
	public class Connect: IMyFunctions, Extensibility.IDTExtensibility2
	{

		// Reference to the Excel application
		private Excel.Application m_xl;

		// The menu item for our command
		private Office.CommandBarButton m_menuItem;

		// Constants for the menu item to create
		private const string m_menuName="Tools";
		private const string m_menuItemCaption="My First C# Excel Add-in";
		private const string m_menuItemKey="MyC#Addin";


		/// <summary>
		///		Implements the constructor for the Add-in object.
		///		Place your initialization code within this method.
		/// </summary>
		public Connect()
		{
		}

		/// <summary>
		///      Implements the OnConnection method of the IDTExtensibility2 interface.
		///      Receives notification that the Add-in is being loaded.
		/// </summary>
		/// <param term='application'>
		///      Root object of the host application.
		/// </param>
		/// <param term='connectMode'>
		///      Describes how the Add-in is being loaded.
		/// </param>
		/// <param term='addInInst'>
		///      Object representing this Add-in.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnConnection(object application, Extensibility.ext_ConnectMode connectMode, object addInInst, ref System.Array custom)
		{
			// Store reference to the Excel host application. Exit if host application is not Excel.
			m_xl=application as Excel.Application;
			if (m_xl==null) return;

			
			// If an addInInst object given of the type COMAddin then loaded as COM Add-in
			// If AddInInst is the same object as myself then I'm loaded as Automation Add-in
			if (addInInst!=this)
			{

				// Attach myself to the add-in object
				// In that way I can call functions of this object from VBA using the add-in collections
				Office.COMAddIn cai=addInInst as Office.COMAddIn;
				cai.Object=this;

				// Now install menu item and add event handler
				m_menuItem = AddInUtils.AddMenuItem(m_xl, cai, m_menuName, m_menuItemCaption, m_menuItemKey);
				m_menuItem.Click+=new Office._CommandBarButtonEvents_ClickEventHandler(MyMenuItemHandler);
			}
		}

		/// <summary>
		///     Implements the OnDisconnection method of the IDTExtensibility2 interface.
		///     Receives notification that the Add-in is being unloaded.
		/// </summary>
		/// <param term='disconnectMode'>
		///      Describes how the Add-in is being unloaded.
		/// </param>
		/// <param term='custom'>
		///      Array of parameters that are host application specific.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnDisconnection(Extensibility.ext_DisconnectMode disconnectMode, ref System.Array custom)
		{
			AddInUtils.RemoveMenuItem(m_xl, disconnectMode, m_menuName, m_menuItemCaption);
		}

		/// <summary>
		///      Implements the OnAddInsUpdate method of the IDTExtensibility2 interface.
		///      Receives notification that the collection of Add-ins has changed.
		/// </summary>
		/// <param term='custom'>
		///      Array of parameters that are host application specific.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnAddInsUpdate(ref System.Array custom)
		{
		}

		/// <summary>
		///      Implements the OnStartupComplete method of the IDTExtensibility2 interface.
		///      Receives notification that the host application has completed loading.
		/// </summary>
		/// <param term='custom'>
		///      Array of parameters that are host application specific.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnStartupComplete(ref System.Array custom)
		{
		}

		/// <summary>
		///      Implements the OnBeginShutdown method of the IDTExtensibility2 interface.
		///      Receives notification that the host application is being unloaded.
		/// </summary>
		/// <param term='custom'>
		///      Array of parameters that are host application specific.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnBeginShutdown(ref System.Array custom)
		{
		}

		// My menu item event handler. Called by Excel.
		private void MyMenuItemHandler(Office.CommandBarButton ctrl, ref bool CancelDefault)
		{
			// Make variable for 'missing' arguments. This is not the same as null
			object missing=System.Reflection.Missing.Value;

			m_xl.get_Range("a1:b2", missing).Value2="Add-in called";
		
		}
		
		// Implementation of the MySubtract interface function
		double IMyFunctions.MySubtract(double value1, double value2)
		{
			return value1-value2;
		}

		// Implementation of the MyAdd interface function
		double IMyFunctions.MyAdd(Excel.Range range)
		{
			int columns=range.Columns.Count;
			int rows=range.Rows.Count;

			// Temporary result
			double tmp=0.0;

			// Iterate the rows and columns
			for (int r=1; r<=rows; r++)
			{
				for (int c=1; c<=columns; c++)
				{
					// Get the value of the current cell as double and add to running result
					tmp+=(double)((Excel.Range)(range[r, c])).Value2;
				}
			}

			// Return result
			return tmp;
		}

	}
}
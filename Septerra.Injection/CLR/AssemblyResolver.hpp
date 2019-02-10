#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Reflection;

namespace SepterraInjection {

	public ref class AssemblyResolver
	{
		public:

		static bool s_initialized = false;

		static void Ensure()
		{
			// System::Diagnostics::Debugger::Launch();
			if (s_initialized)
				return;

			s_initialized = true;

			AppDomain^ currentDomain = AppDomain::CurrentDomain;
			currentDomain->AssemblyResolve += gcnew ResolveEventHandler( AssemblyResolver::MyResolveEventHandler );
		}
		
		static Assembly^ MyResolveEventHandler( Object^ sender, ResolveEventArgs^ args )
		{
			//System::Diagnostics::Debugger::Launch();

			String^ outputDir = BUILD_OUTPUT_DIR;
			outputDir = outputDir->Replace("C=", "C#"); // Idk how to correct this path :(
		    String^ pathToManagedAssembly = Path::Combine(outputDir, GetAssemblyName(args) + ".dll");
		    Assembly^ newAssembly = Assembly::LoadFile(pathToManagedAssembly);
		    return newAssembly;
		}

		static String^ GetAssemblyName (ResolveEventArgs^ args)
		{
			String^ name;
			if (args->Name->IndexOf (",") > -1)
				name = args->Name->Substring (0, args->Name->IndexOf (","));
			else
				name = args->Name;
			return name;
		}
	};
}


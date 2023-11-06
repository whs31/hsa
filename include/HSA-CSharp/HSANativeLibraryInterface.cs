using System;
using System.Runtime.InteropServices;

namespace HSA
{
    public class AdapterInterface
    {
        internal class NativeLibraryInterface
        {
            [UnmanagedFunctionPointer(CallingConvention.StdCall)] 
            public delegate void HSA_TelemetryCallback();

            [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)] 
            public struct HSA_Telemetry
            {
                double latitude;
                double longitude;
                float altitude;
            }
            
            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] 
            public static extern void SetCallback(HSA_TelemetryCallback callback);
            
            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] public static extern void Run();
            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] public static extern void Stop();
            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] public static extern void CreateAdapter();
            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] public static extern void FreeAdapter();
            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] public static extern HSA_Telemetry Read();

            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] public static extern bool IsWin32();
            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] public static extern bool IsPOSIX();
            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] public static extern IntPtr Version();
        }

        public enum NativePlatform
        {
            Win32, 
            POSIX, 
            Unknown
        }

        public static NativePlatform Platform()
        {
            if (NativeLibraryInterface.IsWin32())
                return NativePlatform.Win32;
            else if (NativeLibraryInterface.IsPOSIX())
                return NativePlatform.POSIX;
            return NativePlatform.Unknown;
        }

        public static string Version() { return Marshal.PtrToStringAnsi(NativeLibraryInterface.Version()); }
        
        public static void Start()
        {
            NativeLibraryInterface.HSA_TelemetryCallback callback = () => Console.WriteLine("Ready read!");
            
            NativeLibraryInterface.CreateAdapter();
            NativeLibraryInterface.SetCallback(callback);
            NativeLibraryInterface.Run();
        }
        
        public static void Stop()
        {
            NativeLibraryInterface.Stop();
            NativeLibraryInterface.FreeAdapter();
        }
    }
} // HSA
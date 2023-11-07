using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace HSF.Interop
{
    public static class AdapterInterface
    {
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)] 
        public struct HSA_Telemetry
        {
            public double latitude;
            public double longitude;
            public float altitude;
        }
        
        internal static class NativeLibraryInterface
        {
            [UnmanagedFunctionPointer(CallingConvention.StdCall)] 
            public delegate void HSA_TelemetryCallback();
            
            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] 
            public static extern void Run([MarshalAs(UnmanagedType.FunctionPtr)] HSA_TelemetryCallback callback);
            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] public static extern void Stop();
            
            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] public static extern HSA_Telemetry Read();
            // @TODO set config value
            [DllImport("HSA", CallingConvention = CallingConvention.Cdecl)] public static extern void EnableConsoleLogging();

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
            return NativeLibraryInterface.IsWin32() ? NativePlatform.Win32 : NativeLibraryInterface.IsPOSIX() 
                                                    ? NativePlatform.POSIX : NativePlatform.Unknown;
        }

        public static string Version() { return Marshal.PtrToStringAnsi(NativeLibraryInterface.Version()); }
        
        public static void BeginReceiving(Action onReadyRead)
        {
            NativeLibraryInterface.Run(() =>
            {
                // Debug.Log($"Null? {onReadyRead == null}");
                onReadyRead?.Invoke();
            });
            Debug.Log("<b>HSA Adapter Started.</b>");
        }
        
        public static void EndReceiving()
        {
            NativeLibraryInterface.Stop();
		    Debug.Log("<b>HSA Adapter Stopped.</b>");
        }
        
        public static HSA_Telemetry ReadPacket()
        {
            var telemetry = NativeLibraryInterface.Read();
            return telemetry;
        }
    }
} // HS.Interop
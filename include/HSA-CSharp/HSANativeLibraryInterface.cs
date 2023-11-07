using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace HSF.Interop
{
    public static class AdapterInterface
    {
        internal static class NativeLibraryInterface
        {
            [UnmanagedFunctionPointer(CallingConvention.StdCall)] 
            public delegate void HSA_TelemetryCallback();

            [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)] 
            public struct HSA_Telemetry
            {
                public double latitude;
                public double longitude;
                public float altitude;
            }
            
            
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
        
        public struct Telemetry
        {
            public double Latitude;
            public double Longitude;
            public float Altitude;
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
        
        public static void Start(Action on_ready_read)
        {
            //NativeLibraryInterface.EnableConsoleLogging();
            void Callback()
            {
                var telemetry = AdapterInterface.ReadPacket();
                Debug.Log($"Lat: {telemetry.Latitude}, Lon: {telemetry.Longitude}, Alti: {telemetry.Altitude}");
            }
            //on_ready_read();
            
            NativeLibraryInterface.Run(Callback);
            Debug.Log("<b>HSA Started.</b>");
        }
        
        public static void Stop()
        {
            NativeLibraryInterface.Stop();
		    Debug.Log("<b>HSA Stopped.</b>");
        }
        
        public static Telemetry ReadPacket()
        {
            var raw = NativeLibraryInterface.Read();
            Telemetry ret;
            ret.Latitude = raw.latitude;
            ret.Longitude = raw.longitude;
            ret.Altitude = raw.altitude;
            return ret;
        }
    }
} // HS.Interop
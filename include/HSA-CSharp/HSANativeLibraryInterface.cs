using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace HSA
{
    public class AdapterInterface
    {
        internal class NativeLibraryInterface
        {
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

        public static string Version()
        {
            return Marshal.PtrToStringAnsi(NativeLibraryInterface.Version());
        }
    }
} // HSA
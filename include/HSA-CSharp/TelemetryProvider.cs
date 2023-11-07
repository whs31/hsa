using System;
using UnityEngine;

namespace HSF.Telemetry
{
  public class TelemetryProvider : MonoBehaviour
  {
    public Telemetry Telemetry;
    
    private void Start()
    {
      this.Telemetry = this.GetComponent<Telemetry>();
      Debug.Log($"HSA Adapter Version: {Interop.AdapterInterface.Version()}");
      Debug.Log($"HSA Adapter Native Platform: {Interop.AdapterInterface.Platform()}");
      
      Interop.AdapterInterface.BeginReceiving(this.OnReadyRead);
    }
    
    private void OnReadyRead()
    {
      var raw_telemetry = Interop.AdapterInterface.ReadPacket();
      this.Telemetry.Latitude = raw_telemetry.latitude;
      this.Telemetry.Longitude = raw_telemetry.longitude;
      this.Telemetry.Altitude = raw_telemetry.altitude;
    }

    private void OnDestroy()
    {
      TelemetryProvider.HandleCleanup();
    }

    private static void HandleCleanup()
    {
      Interop.AdapterInterface.EndReceiving();
    }
  }
}
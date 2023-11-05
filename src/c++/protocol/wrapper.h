//
// Created by whs31 on 11/5/2023.
//

#pragma once

#include "parameters.h"

namespace VT45::Structures
{
  namespace Core
  {
    using ACK = core_ack_t;
    using Command = core_cmd_t;
    using Parameter = core_param_t;
    using ParameterGet = core_param_get_t;
    using Message = core_message_t;
    using Version = core_version_t;
    using Firmware = core_firmware_t;
  } // Core

  namespace HeliHW
  {
    using RDDSV = helihw_rddsv_t;
    using Tenso = helihw_tenso_t;
  } // HeliHW

  namespace NavIO
  {
    using Telemetry = navio_telemetry_t;
  } // NavIO

  namespace Heli
  {
    using Telemetry = heli_telemetry_t;
    using SetMode = heli_setmode_t;
    using Control = heli_control_t;
    using Overriders = heli_overriders_t;

    namespace Route
    {
      using Get = heli_route_get_t;
      using GetPoint = heli_route_get_point_t;
      using Data = heli_route_t;
      using Point = heli_route_point_t;
    } // Route

    using Status = heli_status_t;
    using Message = heli_message_t;
  } // Heli

  namespace MAG
  {
    using Telemetry = mag_telemetry_t;
  } // MAG

  namespace Raw
  {
    using MPU9250 = raw_mpu9250_t;
    using LSM9DS1 = raw_lsm9ds1_t;
    using MEMSIC = raw_memsic_t;
    using MS5611 = raw_ms5611_t;
  } // Raw

  namespace VIP
  {
    using Unitdata = vip_unitdata_t;
    using UnitedUnitdata = vip_united_unitdata_t;
  } // VIP

  namespace MRLS
  {
    using Telemetry = mrls_telemetry_t;
  } // MRLS

  namespace AccelerometerGyroscope
  {
    using Telemetry = accgyro_telemetry_t;
  } // AccelerometerGyroscope

  namespace MMS
  {
    using Status = mms_status_t;
    using DecData = mms_dec_data_t;
    using AcmoOut = mms_acmo_out_t;
    using AcmoCoefficient = mms_acmo_coef_t;
    using Command = mms_cmd_t;
    using Novatel = mms_novatel_t;
  } // MMS

  namespace MMS2
  {
    using Course = mms2_course_t;
    using DetectData = mms2_detect_data_t;
  } // MMS2

  namespace Land
  {
    using State = land_state_t;
  } // Land

  namespace Fuel
  {
    using SetCalibrationPoint = fuel_set_calibration_point_t;
    using SetCalibrationInfo = fuel_set_calibration_info_t;
    using CalibrationInfo = fuel_calibration_info_t;
    using Raw = fuel_raw_t;
    using Values = fuel_values_t;
  } // Fuel

  namespace Servo
  {
    using SetParameters = servo_set_params_t;
    using Error = servo_error_t;
    using Parameters = servo_params_t;
    using Telemetry = servo_telemetry_t;
    using MultiSetMode = servo_multi_set_mode_t;
    using SetMode = servo_set_mode_t;
  } // Servo

  namespace Filesystem
  {
    using ReadStopACK = yxfs_file_read_stop_ack_t;
    using ReadStopRequest = yxfs_file_read_stop_req_t;
    using ReadACK = yxfs_file_read_ack_t;
    using ReadRequest = yxfs_file_read_req_t;
    using RenameACK = yxfs_file_rename_ack_t;
    using RenameRequest = yxfs_file_rename_req_t;
    using InfoACK = yxfs_file_info_ack_t;
    using InfoRequest = yxfs_file_info_req_t;
    using EraseACK = yxfs_fs_erase_ack_t;
    using EraseRequest = yxfs_fs_erase_req_t;
    using RemountACK = yxfs_fs_remount_ack_t;
    using RemountRequest = yxfs_fs_remount_req_t;
    using FSInfoACK = yxfs_fs_info_ack_t;
    using FSInfoRequest = yxfs_fs_info_req_t;
  } // Filesystem

  namespace Board
  {
    using ULanding = xboard_ulanding_t;
    using VolFeedback = xboard_volz_feedback_t;
    using VolControl = xboard_volz_control_t;
    using AirSpeed = xboard_airspeed_t;
  } // Board

  namespace RGSound
  {
    using Voice = rgsound_voice_t;
    using VoiceStart = rgsound_voice_start_t;
    using Command = rgsound_cmd_t;
  } // RGSound

  namespace YRaw
  {
    using XSensAllData = yraw_xsens_alldata_t;
    using GKVRawPacket = yraw_gkv_rawpacket_t;
    using ServoControl = yraw_servo_control_t;
    using HMC5883 = yraw_hmc5883_t;
    using ULanding = yraw_ulanding_t;
    using GPS = yraw_gps_t;
  } // YRaw

  namespace ZEkf
  {
    using State = zekf_state_t;
    using Common = zekf_common_t;
  } // ZEkf

  namespace ZImu
  {
    using AirSpeed = zimu_airspeed_t;
    using Range = zimu_range_t;
    using GPS = zimu_gps_t;
    using Baro = zimu_baro_t;
    using MAG = zimu_mag_t;
    using AccelerometerGyroscope = zimu_gyro_acc_t;
  } // ZImu

  namespace ZVisual
  {
    using Euler = zvisual_euler_t;
    using Pos = zvisual_pos_t;
  } // ZVisual

  namespace ZX
  {
    using RTCM = zx_rtcm_t;
    using Antenna = zx_antenna_t;
    using MarsAltimeter = zx_mars_altimeter_t;
  } // ZX

  namespace ZY
  {
    using RionData = zy_rion_data_t;
    using Home = zy_home_t;
  } // ZY

  namespace ZZA
  {
    using SerialForwarderSettings = zza_serial_forwarder_settings_t;
    using SerialForwarderData = zza_serial_forwarder_data_t;
    using CoreData = zza_core_data_t;
  } // ZZA

  namespace ZZB
  {
    using MaxSonarRaw = zzb_maxsonar_raw_t;
    using SBusRaw = zzb_sbus_raw_t;
    using PLKStatus = zzb_plk_status_t;
    using TensoCID = zzb_tenso_cid_t;
  } // ZZB

  namespace ZZC
  {
    using ADCRaw = zzc_adc_raw_t;
    using PWMRaw = zzc_pwm_raw_t;
  } // ZZC

  namespace ZZD
  {
    using TelemetryPath = zzd_telemetry_path_t;
  } // ZZD

  namespace ZZE
  {
    using DADS1Raw = zze_dads1_raw_t;
    using CDMK1Raw = zze_cdmk1_raw_t;
    using AutopilotCPULoad = zze_autopilot_cpu_load_t;
    using FirmwareChecksum = zze_firmware_checksum_t;
  } // ZZE

  namespace ZZF
  {
    using ADS1Raw = zzf_ads1_raw_t;
    using NRA15Raw = zzf_nra15_raw_t;
  } // ZZF

  namespace ZZM
  {
    using Frequency = zzm_frequency_t;
    using Mode = zzm_mode_t;
    using CalibrationCoefficients = zzm_course_coeffs_t;
    using DeviationCoefficients = zzm_deviation_coeffs_t;
    using Course = zzm_course_t;
    using Data = zzm_data_t;
    using DataRaw = zzm_data_raw_t;
  } // ZZM

  namespace ZZN
  {
    using Telemetry = zzn_telemetry_t;
    using PPSFeedback = zzn_pps_feedback_t;
    using PPS = zzn_pps_t;
    using EngineVersion = zzn_engine_version_t;
    using EngineTelemetry = zzn_engine_telem_t;
    using BRP4 = zzn_brp4_t;
    using BRP3 = zzn_brp3_t;
    using BRP2 = zzn_brp2_t;
    using BRP1 = zzn_brp1_t;
    using ServoFeedback = zzn_servo_feedback_t;
    using Servo = zzn_servo_t;
    using Battery = zzn_battery_t;
  } // ZZN

  namespace ZZO
  {
    using CanFrame = zzo_can_frame_t;
    using ExtRaw = zzo_ext_raw_t;
    using AltRaw = zzo_alt1_raw_t;
    using BinsRaw = zzo_bins_raw_t;
    using Bins = zzo_bins_t;
  } // ZZO

  using Protocol = ruavp_protocol_t;
  using Buffer = ruavp_buffer_t;
  using Header = ruavp_header_t;
} // VT45::Structures

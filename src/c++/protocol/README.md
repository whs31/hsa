## Документация по структурам протокола VT45

#### `VT45::Structures::Heli::Telemetry` (`heli_telemetry_t`)
<table>
<tr><th>Имя поля            </th><th>Тип    </th><th>Диапазон значений  </th><th>Описание                       </th></tr>
<tr><th>latitude            </th><th>double </th><th>[-90..90]          </th><th>Широта в градусах              </th></tr>
<tr><th>longitude           </th><th>double </th><th>[-180..180]        </th><th>Долгота в градусах             </th></tr>
<tr><th>dlatitude           </th><th>double </th><th>[-90..90]          </th><th>Заданная широта в градусах     </th></tr>
<tr><th>dlongitude          </th><th>double </th><th>[-180..180]        </th><th>Заданная долгота в градусах    </th></tr>
<tr><th>altitude            </th><th>float  </th><th>[-1000..1000]      </th><th>Высота в метрах (соответствует высоте, используемой автопилотом)</th></tr>
<tr><th>altitude_abs        </th><th>float  </th><th>[-1000..1000]      </th><th>Высота в метрах с датчика абсолютной высоты (GPS/барометр)</th></tr>
<tr><th>daltitude           </th><th>u16    </th><th>[0..1000]          </th><th>Заданная высота в метрах       </th></tr>
<tr><th>ts                  </th><th>u64    </th><th>[0..u64ₘₐₓ]         </th><th>Временная метка в миллисекундах</th></tr>
<tr><th>acceleration_x      </th><th>float  </th><th>[-10⁴..10⁴]        </th><th>Продольное ускорение в м/с²    </th></tr>
<tr><th>acceleration_y      </th><th>float  </th><th>[-10⁴..10⁴]        </th><th>Поперечное ускорение в м/с²    </th></tr>
<tr><th>acceleration_z      </th><th>float  </th><th>[-10⁴..10⁴]        </th><th>Вертикальное ускорение в м/с²  </th></tr>
<tr><th>col_pitch           </th><th>float  </th><th>[-10..10]          </th><th>Шаг основного винта в градусах, деленных на 10</th></tr>
<tr><th>pitch               </th><th>float  </th><th>[-π..π]            </th><th>Тангаж в радианах              </th></tr>
<tr><th>roll                </th><th>float  </th><th>[-π..π]            </th><th>Крен в радианах                </th></tr>
<tr><th>yaw                 </th><th>float  </th><th>[0..2π]            </th><th>Курс в радианах                </th></tr>
<tr><th>target_altitude     </th><th>float  </th><th>[-1000..1000]      </th><th>Высота, определенная через задатчик, в метрах</th></tr>
<tr><th>target_speed        </th><th>float  </th><th>[-1000..1000]      </th><th>Скорость, определенная через задатчик, в м/с</th></tr>
<tr><th>throttle            </th><th>float  </th><th>[0..1]             </th><th>Газ                            </th></tr>
<tr><th>vx                  </th><th>float  </th><th>[-1000..1000]      </th><th>Скорость по продольной оси в м/с</th></tr>
<tr><th>vy                  </th><th>float  </th><th>[-1000..1000]      </th><th>Скорость по поперечной оси в м/с</th></tr>
<tr><th>vz                  </th><th>float  </th><th>[-1000..1000]      </th><th>Скорость по вертикальной оси в м/с</th></tr>
<tr><th>route_point         </th><th>i16    </th><th>[-1..i16ₘₐₓ         </th><th>Номер текущей маршрутной точки </th></tr>
<tr><th>route               </th><th>u8     </th><th>[0..u8ₘₐₓ]          </th><th>Номер текущего маршрута        </th></tr>
<tr><th>rpm_engine          </th><th>u16    </th><th>[0..u16ₘₐₓ]         </th><th>Обороты в минуту первого двигателя</th></tr>
<tr><th>rpm_engine2         </th><th>u16    </th><th>[0..u16ₘₐₓ]         </th><th>Обороты в минуту второго двигателя</th></tr>
<tr><th>rpm_rotor           </th><th>u16    </th><th>[0..u16ₘₐₓ]         </th><th>Обороты в минуту основного винта</th></tr>
<tr><th>rpm_tail            </th><th>u16    </th><th>[0..u16ₘₐₓ]         </th><th>Обороты в минуту хвостового винта</th></tr>
<tr><th>rpm_engine_state    </th><th>u8     </th><th>[0..u8ₘₐₓ]          </th><th>Режим работы двигателя         </th></tr>
<tr><th>mode                </th><th>u8     </th><th>[0..u8ₘₐₓ]          </th><th>Режим работы автопилота        </th></tr>
<tr><th>overriders_state    </th><th>u8     </th><th>[0..u8ₘₐₓ]          </th><th>Битовая маска задатчиков       </th></tr>
</table>

#### `VT45::Structures::NavIO::Telemetry` (`navio_telemetry_t`)
<table>
<tr><th>Имя поля            </th><th>Тип    </th><th>Диапазон значений  </th><th>Описание                       </th></tr>
<tr><th>altitude_barometric </th><th>float</th><th>[-1000..1000]       </th><th>Высота по барометру                                                                   </th></tr>
<tr><th>altitude_gps        </th><th>float</th><th>[-1000..1000]       </th><th>Высота по GPS                                                                         </th></tr>
<tr><th>altitude_radio      </th><th>float</th><th>[0..200]       </th><th>Высота по радиовысотомеру                                                        </th></tr>
<tr><th>gps_course_error    </th><th>float</th><th>[-1000..1000]       </th><th>Погрешность курса по GPS                                                              </th></tr>
<tr><th>gps_velocity_error  </th><th>float</th><th>[-1000..1000]       </th><th>Погрешность скорости по GPS                                                           </th></tr>
<tr><th>roll_velocity       </th><th>float</th><th>[-100..100]       </th><th>Угловая скорость по оси крена в радианах в секунду                                  </th></tr>
<tr><th>roll_velocity_error </th><th>float</th><th>[-1..1]       </th><th>Упр. действие САУ для стабилизации по оси крена                                 </th></tr>
<tr><th>pitch_velocity      </th><th>float</th><th>[-100..100]       </th><th>Угловая скорость по оси тангажа в радианах в секунду                                </th></tr>
<tr><th>pitch_velocity_error</th><th>float</th><th>[-1..1]       </th><th>Упр. действие САУ для стабилизации по оси тангажа                               </th></tr>
<tr><th>yaw_velocity        </th><th>float</th><th>[-100..100]       </th><th>Угловая скорость по оси курса в радианах в секунду                                  </th></tr>
<tr><th>yaw_velocity_error  </th><th>float</th><th>[-1..1]       </th><th>Упр. действие САУ для стабилизации по оси курса                                 </th></tr>
<tr><th>position_x          </th><th>float</th><th>[-10⁵..10⁵]       </th><th>Позиция в метрах по оси, напр. на восток, отн. нач. точки                           </th></tr>
<tr><th>position_x_error    </th><th>float</th><th>[-1000..1000]       </th><th>Погрешность по позиции по оси, напр. на восток                                        </th></tr>
<tr><th>position_x_target   </th><th>float</th><th>[-10⁵..10⁵]       </th><th>Заданная позиция в м по оси, напр. на восток                                        </th></tr>
<tr><th>position_y          </th><th>float</th><th>[-10⁵..10⁵]       </th><th>Позиция в метрах по оси, напр. на север, отн. нач. точки                            </th></tr>
<tr><th>position_y_error    </th><th>float</th><th>[-1000..1000]       </th><th>Погрешность по позиции по оси, напр. на север                                         </th></tr>
<tr><th>position_y_target   </th><th>float</th><th>[-10⁵..10⁵]       </th><th>Заданная позиция в м по оси, напр. на север                                         </th></tr>
<tr><th>position_z_error    </th><th>float</th><th>[-1000..1000]       </th><th>Погрешность по позиции по оси, напр. вниз                                             </th></tr>
<tr><th>signal_roll         </th><th>float</th><th>[-1..1]       </th><th>Значение сигнала по крену с радиоуправления                                     </th></tr>
<tr><th>signal_pitch        </th><th>float</th><th>[-1..1]       </th><th>Значение сигнала по тангажу с радиоуправления                                   </th></tr>
<tr><th>signal_yaw          </th><th>float</th><th>[-1..1]       </th><th>Значение сигнала по курсу с радиоуправления                                     </th></tr>
<tr><th>signal_throttle     </th><th>float</th><th>[-1..1]       </th><th>Значение сигнала по газу/шагу с радиоуправления                                 </th></tr>
<tr><th>target_roll_velocity</th><th>float</th><th>[-100..100]       </th><th>Заданное знач. в рад/с по гироскопической скорости по оси крена                     </th></tr>
<tr><th>target_pitch_velocity</th><th>float</th><th>[-100..100]       </th><th>Заданное знач. в рад/с по гироскопической скорости по оси тангажа                    </th></tr>
<tr><th>target_yaw_velocity </th><th>float</th><th>[-100..100]       </th><th>Заданное знач. в рад/с по гироскопической скорости по оси курса                     </th></tr>
<tr><th>target_altitude     </th><th>float</th><th>[-1000..1000]       </th><th>Заданное знач. в рад/с по высоте в метрах                                             </th></tr>
<tr><th>target_roll         </th><th>float</th><th>[-π..π]       </th><th>Заданное знач. крена в радианах                                                 </th></tr>
<tr><th>target_pitch        </th><th>float</th><th>[-π..π]       </th><th>Заданное знач. тангажа в радианах                                               </th></tr>
<tr><th>target_yaw          </th><th>float</th><th>[0..2π]       </th><th>Заданное знач. по курсу в радианах                                              </th></tr>
<tr><th>target_vx           </th><th>float</th><th>[-100..100]       </th><th>Заданное знач. по поперечной скорости в м/с                                         </th></tr>
<tr><th>target_vy           </th><th>float</th><th>[-100..100]       </th><th>Заданное знач. по продольной скорости в м/с                                         </th></tr>
<tr><th>target_vz           </th><th>float</th><th>[-100..100]       </th><th>Заданное знач. по вертикальной скорости в м/с                                       </th></tr>
<tr><th>target_position_x   </th><th>float</th><th>[-100..100]       </th><th>Заданное знач. позиции в м по оси, напр. на восток                                  </th></tr>
<tr><th>target_position_y   </th><th>float</th><th>[-100..100]       </th><th>Заданное знач. позиции в м по оси, напр. на север                                   </th></tr>
<tr><th>velocity_x_error    </th><th>float</th><th>[-1000..1000]       </th><th>Погрешность скорости по оси, напр. на восток                                          </th></tr>
<tr><th>velocity_y_error    </th><th>float</th><th>[-1000..1000]       </th><th>Погрешность скорости по оси, напр. на север                                           </th></tr>
<tr><th>velocity_z_error    </th><th>float</th><th>[-1000..1000]       </th><th>Погрешность скорости по оси, напр. вниз                                               </th></tr>
</table>                       

#### `VT45::Structures::Heli::Status` (`heli_status_t`)
<table>
<tr><th>Имя поля            </th><th>Тип    </th><th>Диапазон значений  </th><th>Описание                       </th></tr>

<tr><th>last_received_timestamp</th><th>u64 </th><th>[0..u64ₘₐₓ]</th><th>Временная метка последнего пакета с НСУ в миллисекундах</th></tr>
<tr><th>time_left</th><th>float </th><th>[0..10000]</th><th>Время, оставшееся по действию на маршруте              </th></tr>
<tr><th>voltage</th><th>float </th><th>[0..100]</th><th>Напряжение на плате автопилота (В)                     </th></tr>
<tr><th>temperature_engine_left</th><th>i16 </th><th>[-50..200]</th><th>Температура левого цилиндра двигателя                  </th></tr>
<tr><th>temperature_engine_right</th><th>i16 </th><th>[-50..200]</th><th>Температура правого цилиндра двигателя                 </th></tr>
<tr><th>temperature_main_reductor</th><th>i16 </th><th>[-50..200]</th><th>Температура основного редуктора                        </th></tr>
<tr><th>temperature_servo_sp_left</th><th>i16 </th><th>[-50..200]</th><th>Температура левого сервопривода АП                     </th></tr>
<tr><th>temperature_servo_sp_rear</th><th>i16 </th><th>[-50..200]</th><th>Температура заднего сервопривода АП                    </th></tr>
<tr><th>temperature_servo_sp_right</th><th>i16 </th><th>[-50..200]</th><th>Температура правого сервопривода АП                    </th></tr>
<tr><th>temperature_servo_tail</th><th>i16 </th><th>[-50..200]</th><th>Температура хвостового сервопривода                    </th></tr>
<tr><th>temperature_servo_throttle</th><th>i16 </th><th>[-50..200]</th><th>Температура сервопривода газа                          </th></tr>
<tr><th>temperature_tail_reductor</th><th>i16 </th><th>[-50..200]</th><th>Температура хвостового редуктора                       </th></tr>
<tr><th>memsic_state</th><th>u16 </th><th>[0..u8ₘₐₓ]</th><th>Сост. *memsic*                                         </th></tr>
<tr><th>altimeter_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. радиовысотомера                                  </th></tr>
<tr><th>autopilot_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. автопилота                                       </th></tr>
<tr><th>bano_1_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. первого бано                                     </th></tr>
<tr><th>bano_2_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. второго бано                                     </th></tr>
<tr><th>barometer_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. барометрического датчика высоты                  </th></tr>
<tr><th>filesystem_status</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. файловой системы                                 </th></tr>
<tr><th>fuel</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Количество топлива в литрах                            </th></tr>
<tr><th>fuel_sensor_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчиков топлива                                 </th></tr>
<tr><th>gps_1_fixtype</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Тип качества позиционирования у первого модуля GPS     </th></tr>
<tr><th>gps_1_noise</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Разброс в метрах у первого модуля GPS                  </th></tr>
<tr><th>gps_1_satellites</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Количество спутников у первого модуля GPS              </th></tr>
<tr><th>gps_1_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. первого модуля GPS                               </th></tr>
<tr><th>ignition_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. зажигания                                        </th></tr>
<tr><th>imu_1_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. первой инерциальной системы                      </th></tr>
<tr><th>imu_2_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. второй инерциальной системы                      </th></tr>
<tr><th>mag_1_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. первого магнитометра                             </th></tr>
<tr><th>modem_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. модема радиосвязи                                </th></tr>
<tr><th>rc_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. пульта дистанционного радиоуправления            </th></tr>
<tr><th>rpm_engine_2_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика оборотов второго двигателя               </th></tr>
<tr><th>rpm_engine_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика оборотов первого двигателя               </th></tr>
<tr><th>rpm_rotor_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика оборотов основного винта                 </th></tr>
<tr><th>rpm_tail_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. хвостового сервопривода                          </th></tr>
<tr><th>servo_sp_left_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. левого сервопривода тарелки АП                   </th></tr>
<tr><th>servo_sp_rear_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. заднего сервопривода тарелки АП                  </th></tr>
<tr><th>servo_sp_right_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. правого сервопривода тарелки АП                  </th></tr>
<tr><th>servo_tail_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. хвостового сервопривода                          </th></tr>
<tr><th>servo_throttle_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. сервопривода газа                                </th></tr>
<tr><th>t_sensor_engine_left_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика температуры левого цилиндра двигателя    </th></tr>
<tr><th>t_sensor_engine_right_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика температуры правого цилиндра двигателя   </th></tr>
<tr><th>t_sensor_main_reductor_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика температуры основного редуктора          </th></tr>
<tr><th>t_sensor_servo_sp_left_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика температуры левого сервопривода АП       </th></tr>
<tr><th>t_sensor_servo_sp_rear_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика температуры заднего сервопривода АП      </th></tr>
<tr><th>t_sensor_servo_sp_right_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика температуры правого сервопривода АП      </th></tr>
<tr><th>t_sensor_servo_tail_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика температуры хвостового сервопривода      </th></tr>
<tr><th>t_sensor_servo_throttle_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика температуры сервопривода газа            </th></tr>
<tr><th>t_sensor_servo_tail_reductor_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика температуры хвостового редуктора         </th></tr>
<tr><th>tenso_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. датчика обжатия шасси                            </th></tr>
<tr><th>trasser_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. трассера                                         </th></tr>
<tr><th>xboard_state</th><th>u8  </th><th>[0..u8ₘₐₓ]</th><th>Сост. платы расширения автопилота                      </th></tr>
</table>

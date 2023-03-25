import wmi


def get_graphics_driver_version():
    # Create a WMI object to query the system information
    computer = wmi.WMI()
    # Query the version information of the graphics driver
    for adapter in computer.Win32_VideoController():
        version = adapter.DriverVersion
    return version


print(get_graphics_driver_version())

#pragma once

#ifndef geoconvert_h__
#define geoconvert_h__

#if defined(_DLL_BUILD_)
#define GCONV_CALL __declspec(dllexport) int
#elif defined(_DLL_USE_)
#define GCONV_CALL extern "C" __declspec(dllimport) int
#else
#define GCONV_CALL int
#endif

#define GCONV_FAILURE 0
#define GCONV_SUCCESS 1

#ifdef __cplusplus
 extern "C" {
#endif

    GCONV_CALL gconv_wgs84_2_mgrs(char* MGRS,
                                  double Latitude,
                                  double Longitude);

    GCONV_CALL gconv_mgrs_2_wgs84(double* Latitude,
                                  double* Longitude,
                                  const char* MGRS);

    GCONV_CALL gconv_wgs84_2_utm(long   *Zone,
                                 char   *Hemisphere,
                                 double *Easting,
                                 double *Northing,
                                 double Latitude,
                                 double Longitude);

    GCONV_CALL gconv_utm_2_wgs84(double *Latitude,
                                 double *Longitude,
                                 long   Zone,
                                 char   Hemisphere,
                                 double Easting,
                                 double Northing);


#ifdef __cplusplus
    }
#endif

#endif
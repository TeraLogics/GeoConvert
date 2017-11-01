// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include "geoconvert.h"
#include <math.h>
#include "mgrs.h"
#include "utm.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: 
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

/*TEST(geoconvert, wgs_2_utm_2_wgs)
{
	long zone;
	char hemisphere;
	double easting;
	double northing;

	double longitude[4] = { 0, 45, 90, 135 };
	double latitude[2] = { -45, 45 };

	double calculated_latitude;
	double calculated_longitude;

	double allowed_error = 0.00001;

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			EXPECT_EQ(gconv_wgs84_2_utm(&zone, &hemisphere, &easting, &northing, latitude[j], longitude[i]), GCONV_SUCCESS);
			EXPECT_EQ(gconv_utm_2_wgs84(&calculated_latitude, &calculated_longitude, zone, hemisphere, easting, northing), GCONV_SUCCESS);
			EXPECT_TRUE(allowed_error > abs((latitude[j] - calculated_latitude)));
			EXPECT_TRUE(allowed_error > abs((longitude[i] - calculated_longitude)));
		}
	}
}

TEST(geoconvert, wgs_2_mgrs_2_wgs)
{
	char mgrs[256];
	double longitude[4] = { 0, 45, 90, 135 };
	double latitude[2] = { -45, 45 };

	double calculated_latitude;
	double calculated_longitude;

	double allowed_error = 0.00001;

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			EXPECT_EQ(gconv_wgs84_2_mgrs(mgrs, latitude[j], longitude[i]), GCONV_SUCCESS);
			EXPECT_EQ(gconv_mgrs_2_wgs84(&calculated_latitude, &calculated_longitude, mgrs), GCONV_SUCCESS);
			EXPECT_TRUE(allowed_error > abs((latitude[j] - calculated_latitude)));
			EXPECT_TRUE(allowed_error > abs((longitude[i] - calculated_longitude)));
		}
	}
}

TEST(geoconvert, wgs_2_mgrs_2_wgs_for_specific_lat_lon_values)
{
	char mgrs[256];
	double longitude[3] = { 0, 90, -90 };
	double latitude = 72;
	double calculated_latitude;
	double calculated_longitude;
	double allowed_error = 0.00001;

	for (int i = 0; i < 3; i++)
	{
		EXPECT_EQ(gconv_wgs84_2_mgrs(mgrs, latitude, longitude[i]), GCONV_SUCCESS);
		EXPECT_EQ(gconv_mgrs_2_wgs84(&calculated_latitude, &calculated_longitude, mgrs), GCONV_SUCCESS);
		EXPECT_TRUE(allowed_error > abs((latitude - calculated_latitude)));
		EXPECT_TRUE(allowed_error > abs((longitude[i] - calculated_longitude)));
	}
}

TEST(geoconvert, wgs_2_mgrs_2_wgs_for_long_180)
{
	char mgrs[256];
	double longitude = 180;
	double latitude = 72;
	double calculated_latitude;
	double calculated_longitude;
	double allowed_error = 0.00001;

	EXPECT_EQ(gconv_wgs84_2_mgrs(mgrs, latitude, longitude), GCONV_SUCCESS);
	EXPECT_EQ(gconv_mgrs_2_wgs84(&calculated_latitude, &calculated_longitude, mgrs), GCONV_SUCCESS);
	EXPECT_TRUE(allowed_error > abs((latitude - abs(calculated_latitude))));
	EXPECT_TRUE(allowed_error > abs((longitude - abs(calculated_longitude))));
}

TEST(geoconvert, wgs_2_utm_2_wgs_for_long_180)
{
	long zone;
	char hemisphere;
	double easting;
	double northing;

	double longitude = 180;
	double latitude[2] = { -45, 45 };

	double calculated_latitude;
	double calculated_longitude;

	double allowed_error = 0.00001;

	for (int j = 0; j < 2; j++)
	{

		EXPECT_EQ(gconv_wgs84_2_utm(&zone, &hemisphere, &easting, &northing, latitude[j], longitude), GCONV_SUCCESS);
		EXPECT_EQ(gconv_utm_2_wgs84(&calculated_latitude, &calculated_longitude, zone, hemisphere, easting, northing), GCONV_SUCCESS);
		EXPECT_TRUE(allowed_error > abs((latitude[j] - calculated_latitude)));
		EXPECT_TRUE(allowed_error > abs((longitude - abs(calculated_longitude))));

	}
}

TEST(geoconvert, usage_with_bad_values)
{
	char	mgrs[256];
	char*	bad_mgrs = "badval";
	double	longitude = 200;
	double	latitude = 200;
	long	zone;
	char	hemisphere;
	double	easting;
	double	northing;
	double	calculated_latitude;
	double	calculated_longitude;

	EXPECT_EQ(gconv_wgs84_2_mgrs(mgrs, latitude, longitude), GCONV_FAILURE);
	EXPECT_EQ(gconv_mgrs_2_wgs84(&calculated_latitude, &calculated_longitude, bad_mgrs), GCONV_FAILURE);
	EXPECT_EQ(gconv_utm_2_wgs84(&calculated_latitude, &calculated_longitude, 2012, 'D', 0, 0), GCONV_FAILURE);
	EXPECT_EQ(gconv_wgs84_2_utm(&zone, &hemisphere, &easting, &northing, latitude, longitude), GCONV_FAILURE);
}*/

extern "C"
{
    const double PI = 3.14159265358979323846;

    GCONV_CALL gconv_wgs84_2_mgrs(char* MGRS,
                                  double Latitude,
                                  double Longitude)
    {
        double lat = Latitude*PI/180.0;
        double lng = Longitude*PI/180.0; 

        int status = Convert_Geodetic_To_MGRS(lat, lng, 5, MGRS);
        return (status != MGRS_NO_ERROR) ? GCONV_FAILURE : GCONV_SUCCESS;
    }

    GCONV_CALL gconv_mgrs_2_wgs84(double* Latitude,
                                  double* Longitude,
                                  const char* MGRS)
    {
        double lat = 0;
        double lng = 0;

        int status = Convert_MGRS_To_Geodetic((char*)MGRS, &lat, &lng);

        *Latitude  = lat*180.0/PI;
        *Longitude = lng*180.0/PI;

        return (status != MGRS_NO_ERROR) ? GCONV_FAILURE : GCONV_SUCCESS;
    }

    GCONV_CALL gconv_wgs84_2_utm(long   *Zone,
                                 char   *Hemisphere,
                                 double *Easting,
                                 double *Northing,
                                 double Latitude,
                                 double Longitude)
    {
        double lat = Latitude*PI/180.0;
        double lng = Longitude*PI/180.0; 

        int status = Convert_Geodetic_To_UTM(lat, lng, Zone, Hemisphere, Easting, Northing);

        return (status != UTM_NO_ERROR) ? GCONV_FAILURE : GCONV_SUCCESS;
    }

    GCONV_CALL gconv_utm_2_wgs84(double *Latitude,
                                 double *Longitude,
                                 long   Zone,
                                 char   Hemisphere,
                                 double Easting,
                                 double Northing)
    {
        double lat = 0;
        double lng = 0;

        int status = Convert_UTM_To_Geodetic(Zone, Hemisphere, Easting, Northing, &lat, &lng);

        *Latitude  = lat*180.0/PI;
        *Longitude = lng*180.0/PI;

        return (status != UTM_NO_ERROR) ? GCONV_FAILURE : GCONV_SUCCESS;
    }
}

/*
 * sun_tracker.c
 *
 *  Created on: 5 avr. 2019
 *      Author: Nirgal
 */


#include "sun_tracker.h"
#include "SolTrack.h"	//librairie de calcul de la position du soleil
#include "stm32f1_rtc.h"
#include "systick.h"
#include "secretary.h"
#include <stdint.h> // types

//R�glages de la librairie SolTrack :
#define	USE_DEGREES						1		// Input (geographic position) and output are in degrees
#define USE_NORTH_EQUALS_ZERO			1		// Azimuth: 0 = North, pi/2 (90deg) = East
#define COMPUTE_REFRACTION_EQUATORIAL	1		// Compute refraction-corrected equatorial coordinates (Hour angle, declination): 0-no, 1-yes
#define	COMPUTE_DISTANCE				1		// Compute the distance to the Sun in AU: 0-no, 1-yes


static SolTrackLocation_t loc;
static void process_ms(void);
static void SUN_TRACKER_compute_sun_position(SolTrackTime_t * time, SolTrackPosition_t * pos, SolTrackRiseSet_t * riseSet);


void SUN_TRACKER_init(void)
{
	RTC_init(TRUE);

	//Donn�es par d�faut - position de l'ESEO - Angers
	loc.latitude = 47.4933;
	loc.longitude = -0.5508;
	loc.pressure = 101.3;		//En haut du batiment, on est plus haut qu'en bas... mais globalement pas loin du niveau de la mer.
								//on n�glige les effets de l'altitude
	loc.temperature = 283.0;  	// Atmospheric temperature in K

	//Il faut bien d�marrer avec une horaire de d�part.
	RTC_DateTypeDef currentDate;
	RTC_TimeTypeDef currentTime;
	currentDate.Date = 1;
	currentDate.Month = 4;
	currentDate.Year = 19;
	currentTime.Hours = 8;		//attention � renseigner l'heure GMT
	currentTime.Minutes = 0;
	currentTime.Seconds = 0;
	RTC_set_time_and_date(&currentTime, &currentDate);

	Systick_add_callback_function(&process_ms);
}

volatile bool_e flag_1s = FALSE;

static void process_ms(void)
{
	static uint16_t t_ms = 0;
	if(t_ms == 0)
	{
		t_ms = 1000;
		flag_1s = TRUE;
	}
	t_ms--;

}

void SUN_TRACKER_process_main(void)
{
	SECRETARY_process_main();
	if(flag_1s)
	{
		flag_1s = FALSE;
		HAL_GPIO_TogglePin(LED_GREEN_GPIO, LED_GREEN_PIN);
		
		SolTrackTime_t time;
		//donn�es de test temporaires.
		time.year = 	(int32_t)(20) + 2000;	//2020
		time.month = 	(int32_t)(4);			//avril
		time.day = 		(int32_t)(1);			//1er
		time.hour = 	(int32_t)(8);
		time.minute = 	(int32_t)(30);
		time.second = 	(double)(40.4);


		//variable qui serviront � receuillir les r�sultats des calculs
		SolTrackPosition_t pos;
		SolTrackRiseSet_t riseSet;

		//calculs
		SUN_TRACKER_compute_sun_position(&time, &pos, &riseSet);
	}
}


static void SUN_TRACKER_compute_sun_position(SolTrackTime_t * time, SolTrackPosition_t * pos, SolTrackRiseSet_t * riseSet)
{
	// Compute rise and set times:
	SolTrack_RiseSet(time, &loc, pos, riseSet, 0.0, USE_DEGREES, USE_NORTH_EQUALS_ZERO);

	// Compute positions:
	SolTrack(time, &loc, pos, USE_DEGREES, USE_NORTH_EQUALS_ZERO, COMPUTE_REFRACTION_EQUATORIAL, COMPUTE_DISTANCE);
}

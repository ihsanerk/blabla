#ifndef TRACKER_H
#define	TRACKER_H

#include <stdbool.h>

/**
 *  \file tracker.h
 *  \brief Tracks the absolute position of the robot and the objective
 *
 *  Also sends relative error to the objective to the controller
 */

/**
 *  \brief Set a new objective in absolute position
 *
 *  \param [in] objective_x x position in meter
 *  \param [in] objective_y y position in meter
 */
void trackerSetObjective(float x, float y, float angle);
/**
 *  \brief Set the robot's absolute position
 *
 *  \param [in] new_position_x x position in meter
 *  \param [in] new_position_y y position in meter
 */
void trackerSetPosition(float new_position_x, float new_position_y, float new_position_angle);
/**
 *  \brief Updates the robot's position and send error to the objective to the controller
 *
 *  \param [in] time_elapsed time elapsed since last call
 */
void trackerUpdate();


bool trackerIsPositionAtObjective();

void trackerLogPosition(void);

extern bool isAngleAbsolute;

void trackerDebugPosition(void);
void trackerDebugObjective(void);

#endif	/* TRACKER_H */


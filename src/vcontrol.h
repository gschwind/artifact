/*
 * Copyright 2010 Benoit Gschwind <gschwind@gnu-log.net>
 *
 * This file is part of artifact.
 *
 * artifact is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * artifact is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with artifact.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VCONTROL_HPP_
#define VCONTROL_HPP_

class vcontrol {
public:
	vcontrol();
	virtual ~vcontrol();

	virtual void joy_left_press();
	virtual void joy_left_release();

	virtual void joy_right_press();
	virtual void joy_right_release();

	virtual void joy_up_press();
	virtual void joy_up_release();

	virtual void joy_down_press();
	virtual void joy_down_release();

	virtual void joy_button0_press();
	virtual void joy_button0_release();

	virtual void joy_button1_press();
	virtual void joy_button1_release();

	virtual void joy_button2_press();
	virtual void joy_button2_release();

	virtual void joy_button3_press();
	virtual void joy_button3_release();

	virtual void joy_button4_press();
	virtual void joy_button4_release();

	virtual void joy_button5_press();
	virtual void joy_button5_release();

	virtual void joy_button6_press();
	virtual void joy_button6_release();

	virtual void joy_button7_press();
	virtual void joy_button7_release();

};

#endif /* VCONTROL_H_ */

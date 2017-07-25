class Time {
	public: 
	int hours;
	int minute;
	Time(int hours, int minute) {
		if ((hours / 13) || (minute / 60)) {
			 this->hours = 0;
			 this->minute = 0;
		} else {
			this->hours = hours;
			this->minute = minute;
		}
	};
	Time operator + (Time t) {
		int i = 0;
		if ((this->hours + t.hours + (this->minute + t.minute)/60) >= 13) i = 1;
		return Time((this->hours + t.hours + (this->minute + t.minute)/60)%13 + i, ((this->minute + t.minute)%60));
	};
	bool operator == (Time t);
	
};

bool Time::operator == (Time t) {
	if ((t.hours == this->hours) && (t.minute == this->minute)) return true;
	return false;
}

std::ostream & operator <<( std::ostream &os, const Time &t )
{
	if (t.minute < 10) return os << t.hours << ".0" << t.minute;
	return os << t.hours << "." << t.minute;
}

typedef struct
{
	double dState; // Last position input
	double iState; // Integrator state
	double iMax, iMin; // Maximum and minimum allowable integrator state
	double iGain, // integral gain
	pGain, // proportional gain
	dGain; // derivative gain
} SPid;

double UpdatePID(SPid * pid, double error, double position);
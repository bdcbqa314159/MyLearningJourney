// newh.hxx


// Other functions
T probability(const T& a, const T& b) const;	// Probability of being in interval [a,b]
T mgf(const T& t) const;	// Moment-generating function
T moment(int k) const;		// The moment (higher-order expectations)
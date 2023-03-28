// CooneyExcel.hpp
//
// Support class to send output to excel
//
// (C) Datasim Component Technology 2000

#ifndef CooneyExcel_hpp
#define CooneyExcel_hpp

#include "NumericMatrix.hpp"
#include "ExcelDriver.hpp"
#include <string>

class CooneyExcel
{
private:
	Datasim::NumericMatrix<double, int, Datasim::FullMatrix<double>, Datasim::FullArray<double> > m_matrix;

	void FillNormal(struct Params& param, struct SolSettings& setting, ExcelDriver& xl);
	void FillDelta1(struct Params& param, struct SolSettings& setting, ExcelDriver& xl);
	void FillDelta2(struct Params& param, struct SolSettings& setting, ExcelDriver& xl);
	void FillDelta3(struct Params& param, struct SolSettings& setting, ExcelDriver& xl);

	std::string SerieText(struct Params& param, int serie);
	std::string ChartTitleText(struct Params& param, struct SolSettings& setting);
	std::string CategoryText(struct Params& param);
	std::string ValueText(struct Params& param);

public:
	CooneyExcel();
	CooneyExcel(int rows, int columns);
	~CooneyExcel();

	void AddSerie(double *x, int t_index);
	bool ToExcel(struct Params& param, struct SolSettings& setting);
};

#endif

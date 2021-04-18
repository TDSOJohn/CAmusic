#ifndef dataanalyzer_hpp
#define dataanalyzer_hpp


class DataAnalyzer
{
public:
                                    DataAnalyzer();
                                    DataAnalyzer(std::vector<std::vector<int> > const& data_in);

    void                            addData(std::vetor<int> const& data_in);
    std::vector<std::vector<int> >  returnData();
};


#endif //dataanalyzer_hpp

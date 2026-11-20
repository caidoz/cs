#pragma once
// Construct legacy fixtures without pretending the current wire layout is old.
inline std::string legacySnapshotV13(const MergeRoulette::Run& run){
    std::istringstream input(run.encode());std::vector<std::string> fields;std::string field;
    while(input>>field)fields.push_back(field);
    size_t cursor=2+15+3+2+MergeRoulette::Height;
    for(int list=0;list<2;++list){
        const int count=std::stoi(fields[cursor++]);
        for(int n=0;n<count;++n){cursor+=6;fields.erase(fields.begin()+cursor,fields.begin()+cursor+6);}
    }
    fields[1]="13";std::ostringstream out;
    for(size_t n=0;n<fields.size();++n){if(n)out<<' ';out<<fields[n];}
    return out.str();
}

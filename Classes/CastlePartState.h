#pragma once
namespace CastleParts {
enum Part { Roof, Trim, Room, Cannon, Mobility, PartCount };
enum { CastleCount = 10, LevelCount = 5 };
struct State {
    int castle;
    int level[CastleCount][PartCount];
    State() { reset(); }
    void reset() { castle=0; for(int c=0;c<CastleCount;++c) for(int p=0;p<PartCount;++p) level[c][p]=1; }
    void nextPart(int p) { if(p>=0&&p<PartCount) level[castle][p]=level[castle][p]%LevelCount+1; }
    void nextAll() { for(int p=0;p<PartCount;++p) nextPart(p); }
    void previousCastle() { castle=(castle+CastleCount-1)%CastleCount; }
    void nextCastle() { castle=(castle+1)%CastleCount; }
};
}

#pragma once

class ManagerBase {
public:
    virtual ~ManagerBase() = default;

    virtual void Init() {}              
    virtual void Update() = 0;         
    virtual void CleanUp() {}
};

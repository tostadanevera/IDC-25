#pragma once

class OutputDevices {
public:
    virtual void grantAccess() = 0;
    virtual void denyAccess() = 0;
    virtual ~OutputDevices() = default;
};

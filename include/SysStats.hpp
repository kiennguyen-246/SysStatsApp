#ifndef SYSSTATS_GUARD
#define SYSSTATS_GUARD

class SysStats {
    public:
    /**
     * Get the resource used by processes within the last retrieval interval
    */
    virtual double getCurrentUsed() = 0;
    /**
     * Get the total resource of the system within the last retrieval interval
    */
    virtual double getCurrentTotal() = 0;

    /**
     * Get the resource usage percentage of the system within the last retrieval interval
    */
    virtual double getCurrentUsage() = 0;
};

#endif
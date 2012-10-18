// EnrichmentFacility.h
#ifndef _ENRICHMENTFACILITY_H
#define _ENRICHMENTFACILITY_H

#include "FacilityModel.h"

#include "MatBuff.h"

#include <deque>

// forward declarations
class QueryEngine;

/**
   @class EnrichmentFacility 
    
   @section introduction Introduction 
 */
class EnrichmentFacility : public FacilityModel
{
  /* --- EnrichmentFacility Classes --- */
  class Assays
  {
  public:
    /// constructor, an error flag is set if the fractions don't equal 1
    Assays(double feed, double product, double tails);
    
    /// returns the feed assay, but throws an error if the fractions don't equal 1
    double feed();

    /// returns the product assay, but throws an error if the fractions don't equal 1
    double product();

    /// returns the tails assay, but throws an error if the fractions don't equal 1
    double tails();

  private:
    double feed_, product_, tails_;
    bool error_;
    void checkSum();
  };
  /* --- */

 public:
  /* --- Module Methods --- */
  /**
     Default Constructor for the EnrichmentFacility class 
   */
  EnrichmentFacility();
  
  /**
     Destructor for the EnrichmentFacility class 
   */
  virtual ~EnrichmentFacility();
 
  /**
     Initialize members related to derived module class
     @param qe a pointer to a QueryEngine object containing initialization data
   */
  virtual void initModuleMembers(QueryEngine* qe);

  /**
     Print information about this model 
   */
  virtual std::string str();
  /* --- */

  /* --- Facility Methods --- */
  /**
     Copy module members from a source model
     @param sourceModel the model to copy from
   */
  virtual void cloneModuleMembersFrom(FacilityModel* sourceModel);
  /* --- */

  /* --- Agent Methods --- */
  /**
     Each facility is prompted to do its beginning-of-time-step 
     stuff at the tick of the timer. 
      
     @param time is the time to perform the tick 
   */
  virtual void handleTick(int time);

  /**
     Each facility is prompted to its end-of-time-step 
     stuff on the tock of the timer. 
      
     @param time is the time to perform the tock 
   */
  virtual void handleTock(int time);
  /* --- */

  /* --- Transaction Methods --- */
  /**
     When this facility receives a message, execute the transaction 
   */
  virtual void receiveMessage(msg_ptr msg);

  /**
     Transacted resources are extracted through this method       
     @param order the msg/order for which resource(s) are to be prepared 
     @return list of resources to be sent for this order 
      
   */ 
  virtual std::vector<rsrc_ptr> removeResource(Transaction order);

  /**
     Transacted resources are received through this method 
     @param trans the transaction to which these resource objects belong 
     @param manifest is the set of resources being received 
   */ 
  virtual void addResource(Transaction trans,
                           std::vector<rsrc_ptr> manifest);
  /* --- */

  /* --- EnrichmentFacility Methods --- */  
  /* --- */

 protected:  
  /* --- Transaction Methods --- */     
  /**
     sends a transaction as an offer 
   */
  void sendOffer(Transaction trans);
  /* --- */

  /* --- EnrichmentFacility Members and Methods --- */  
  /* --- */
};

#endif


#ifndef MAIN_FILE_H    
#define MAIN_FILE_H   


  #ifdef __cplusplus
  extern "C"{
  #endif


    /********************START OF BOUNDARY MODULE SECTION********************/
      extern int currentState;

      #define NORMAL_STATE 0
      #define OBSTACLE_DETECTED_STATE 1
      #define BOUNDARY_DETECTED_STATE 2
    /********************END OF BOUNDARY MODULE SECTION********************/

    
    /********************START OF MOVEMENT MODULE SECTION********************/
      #define LEFT_SIDE_DIRECTION_PIN 50
      #define LEFT_SIDE_ENABLE_PIN 51
     
      #define RIGHT_SIDE_DIRECTION_PIN  49
      #define RIGHT_SIDE_ENABLE_PIN 48

      void setupMovementModule(void);

      void turnLeft();
      void turnRight();

      void moveForward() ;
      void moveBackward();
    /********************END OF MOVEMENT MODULE SECTION********************/


    /********************START OF OBSTACLE MODULE SECTION********************/
      #define TIME_OF_FLIGHT_DISTANCE_SENSOR_IRQ_PIN 2
      #define TIME_OF_FLIGHT_DISTANCE_SENSOR_XSHUT_PIN 3
      
      extern bool isObstacleDetected;
      void setUpObstacleModule(void);
      void checkObstacle(void);
    /********************END OF OBSTACLE MODULE SECTION********************/


    /********************START OF BOUNDARY MODULE SECTION********************/

    #define LEFT_LINE_DETECTION_OUT_PIN 6
    #define CENTER_LINE_DETECTION_OUT_PIN 7
    #define RIGHT_LINE_DETECTION_OUT_PIN 8
    
    
    extern bool isBoundaryDetected;

    void setupBoundaryModule(void);
    void checkBoundary(void);

    /********************END OF BOUNDARY MODULE SECTION********************/






    #ifdef __cplusplus
    } // extern "C"
    #endif

#endif

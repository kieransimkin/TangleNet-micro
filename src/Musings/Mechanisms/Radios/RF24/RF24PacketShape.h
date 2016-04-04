
#include <stdint.h>

// used to announce presence on the network
#define MSG_TYPE_SMILE 0 
// used to confirm receipt of a message
#define MSG_TYPE_NOD 1
#define MSG_TYPE_COLLISION 2
#define MSG_TYPE_RESEND 3
#define MSG_TYPE_SIGN 4
#define MSG_TYPE_REMISS 5
#define MSG_TYPE_ROUSE 6
#define MSG_TYPE_ASTRAY 7
#define MSG_TYPE_NEST 8
#define MSG_TYPE_INTERROGATE 9
#define MSG_TYPE_PRANCE 10
#define MSG_TYPE_QRK 11
#define MSG_TYPE_CRITIQUE 12
#define MSG_TYPE_DRIFT 13
#define MSG_TYPE_STREETPARTY 14
#define MSG_TYPE_HOBNOB 15
#define MSG_TYPE_OBSERVATION 16
#define MSG_TYPE_EVENT 17
#define MSG_TYPE_ALERT 18
#define MSG_TYPE_ACTION 19
#define MSG_TYPE_SCOUTING 20

#define MSG_FLAG_BEGIN 1
#define MSG_FLAG_END 2
#define MSG_FLAG_ECHO 4
#define MSG_FLAG_SIGNED 8
#define MSG_FLAG_RETRANSMIT 16
#define MSG_FLAG_FORWARDED 32

#include <Arduino.h>

struct RF24Packet {
	uint8_t MessageType;
	uint8_t Sequence;
	uint8_t Flags;
	uint8_t KnotLinkID[3];
 	uint8_t Payload[28];	
};
/*
// SMILE
typedef struct {
	uint8_t ecdsaPublic[uECC_BYTES+1];
} RF24MSG_Smile;

// NOD
typedef struct {
	uint8_t ecdsaPublic[uECC_BYTES+1];
} RF24MSG_Nod;

// REMISS
typedef struct {
	uint8_t FussinessFactors;
} RF24MSG_Remiss;

*/
#define TEMPORAL_FUSSINESS_RTC 1;
#define TEMPORAL_FUSSINESS_NTP 2;
#define TEMPORAL_FUSSINESS_GPS 4;
#define TEMPORAL_FUSSINESS_RF 8;
#define TEMPORAL_FUSSINESS_RUBIDIUM 16;
#define TEMPORAL_FUSSINESS_CAESEUM 32;
#define TEMPORAL_FUSSINESS_TIMELORD 64;

class RF24Message {
	private:
	RF24Packet *data;
	public:
	RF24Message(char *raw);
};


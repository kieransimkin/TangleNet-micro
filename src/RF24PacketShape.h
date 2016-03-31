#define MSG_TYPE_SMILE 0 
#define MSG_TYPE_NOD 1
#define MSG_TYPE_SIGN 2
#define MSG_TYPE_REMISS 3
#define MSG_TYPE ROUSE 4
#define MSG_TYPE_ASTRAY 5
#define MSG_TYPE_NEST 6
#define MSG_TYPE_INTERROGATE 7
#define MSG_TYPE_PRANCE 8
#define MSG_TYPE QRK 9
#define MSG_TYPE_CRITIQUE 10
#define MSG_TYPE_DRIFT 11
#define MSG_TYPE_STREETPARTY 12
#define MSG_TYPE_HOBNOB 13
#define MSG_TYPE_OBSERVATION 14
#define MSG_TYPE_EVENT 15
#define MSG_TYPE_ALERT 16
#define MSG_TYPE ACTION 17
#define MSG_TYPE SCOUTING 18


typedef struct {
	uint8_t MessageType,
	uint8_t FragmentNumber,
	uint8_t Sequence,
	uint8_t Flags,
	uint8_t KnotLinkID[3],
 	uint8_t Payload[27]	
} RF24Packet;
typedef struct {
	uint8_t ecdsaPublic[uECC_BYTES+1];
} RF24MSG_Smile;
typedef struct {
	uint8_t ecdsaPublic[uECC_BYTES+1];
} RF24MSG_Nod;
typedef struct {
	uint8_t FussinessFactors;
} RF24MSG_Remiss;
#define TEMPORAL_FUSSINESS_RTC 1;
#define TEMPORAL_FUSSINESS_NTP 2;
#define TEMPORAL_FUSSINESS_GPS 4;
#define TEMPORAL_FUSSINESS_RF 8;
#define TEMPORAL_FUSSINESS_RUBIDIUM 16;
#define TEMPORAL_FUSSINESS_CAESEUM 32;
#define TEMPORAL_FUSSINESS_TIMELORD 64;

class RF24Message {
	private:
	RF24Packet data;
	public:
	RF24Message(uint8_t[32] raw);
};


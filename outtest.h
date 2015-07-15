#ifndef _INCLUDETOKEN_2_H_
#define _INCLUDETOKEN_2_H_

#include <stdio.h>
// Auto generated code by packdef2code
// Version: 3.3
// Desc: CIGI 3.3 packet definition format

namespace Cigi33
{
//===------------------------------===//
// Base packet class
// 
//===------------------------------===//
class BasePacket
{
public:
	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s){ return 0; }
	virtual size_t saveToBinaryStream(unsigned char* data, size_t s){ return 0; }
	virtual unsigned int getType(){ return 0; }
};

//===------------------------------===//
// Helper functions
// 
//===------------------------------===//
template<typename N, unsigned int S, unsigned int C> inline unsigned int extractBits(N number)
{
	unsigned int t = (unsigned int)((1<<C)-1);
	t = t<<S;
	return (unsigned int)( (t&number) >> S);
}

template<typename T, unsigned int S, unsigned int C> inline void setBits( T& r, unsigned int value )
{
	unsigned int m = (1<<C)-1;
	unsigned int n = ~(m << S) & (unsigned int)(r);
	unsigned int v = (~m & value) << S;
	r = (T)(n|v);
}

struct DataPtrReader
{
	DataPtrReader ( const unsigned char* ptr, int s ) : ptr(ptr),size(s), rem(s){}
	template<typename T> T get()
	{
		if ( rem <= 0 ) return T();
		T* p = (T*)ptr; 
		T ret = *p;
		++p;
		rem -= sizeof(T);
		ptr = (unsigned char*)p;
		return ret;
	}
	const unsigned char* ptr;
	int size;
	int rem;
};

struct DataPtrWriter
{
	DataPtrWriter(unsigned char* ptr, int s ): ptr(ptr), size(s), rem(s){}
	template<typename T> void set( T value )
	{
		T* p = (T*)ptr;
		*p = value;
		++p;
		rem -= sizeof(T);
		ptr = (unsigned char*)p;
	}
	unsigned char* ptr;
	int size;
	int rem;
};

//===------------------------------===//
// Enumerations
// 
//===------------------------------===//
enum IGModeState
{
	IGMS_Reset_Standby = 0,
	IGMS_Operate = 1,
	IGMS_Debug = 2,
	IGMS_Offline_Maintenance = 3,
};

enum EntityState
{
	ES_Inactive_Standby = 0,
	ES_Active = 1,
	ES_Destroyed = 2,
};

enum TimestampState
{
	TSS_Invalid = 0,
	TSS_Valid = 1,
};

enum AttachState
{
	AS_Detach = 0,
	AS_Attach = 1,
};

enum GenericBoolState
{
	GBS_Disabled = 0,
	GBS_Enabled = 1,
};

enum GenericValidState
{
	VS_Invalid = 0,
	VS_Valid = 1,
};

enum VisibleState
{
	VS_Occluded = 0,
	VS_Visible = 1,
};

enum InheritAlphaState
{
	IAS_Not_Inherited = 0,
	IAS_Inherited = 1,
};

enum ClampState
{
	CLAMP_No_Clamp = 0,
	CLAMP_Non_Conformal = 1,
	CLAMP_Conformal = 2,
};

enum AnimDirectionState
{
	ANIMDIR_Forward = 0,
	ANIMDIR_Backward = 1,
};

enum AnimLoopMode
{
	ANIMLOOP_One_Shot = 0,
	ANIMLOOP_Continuous = 1,
};

enum AnimState
{
	ANIM_Stop = 0,
	ANIM_Pause = 1,
	ANIM_Play = 2,
	ANIM_Continue = 3,
};

enum DOFSelectState
{
	DOFSEL_Not_Used = 0,
	DOFSEL_X_Offset = 1,
	DOFSEL_Y_Offset = 2,
	DOFSEL_Z_Offset = 3,
	DOFSEL_Yaw = 4,
	DOFSEL_Pitch = 5,
	DOFSEL_Roll = 6,
};

enum RateControlCSState
{
	RCCS_World_Parent = 0,
	RCCS_Local = 1,
};

enum WeatherLayerState
{
	LAYER_Ground_Fog = 0,
	LAYER_Cloud_Layer_1 = 1,
	LAYER_Cloud_Layer_2 = 2,
	LAYER_Cloud_Layer_3 = 3,
	LAYER_Rain = 4,
	LAYER_Snow = 5,
	LAYER_Sleet = 6,
	LAYER_Hail = 7,
	LAYER_Sand = 8,
	LAYER_Dust = 9,
};

enum WeatherCloudType
{
	CLOUD_None = 0,
	CLOUD_Altocumulus = 1,
	CLOUD_Altostratus = 2,
	CLOUD_Cirrocumulus = 3,
	CLOUD_Cirrostratus = 4,
	CLOUD_Cirrus = 5,
	CLOUD_Cumulonimbus = 6,
	CLOUD_Cumulus = 7,
	CLOUD_Nimbostratus = 8,
	CLOUD_Stratocumulus = 9,
	CLOUD_Stratus = 10,
	CLOUD_Custom_1 = 11,
	CLOUD_Custom_2 = 12,
	CLOUD_Custom_3 = 13,
	CLOUD_Custom_4 = 14,
	CLOUD_Custom_5 = 15,
};

enum WeatherScopeState
{
	SCOPE_Global = 0,
	SCOPE_Regional = 1,
	SCOPE_Entity = 2,
};

enum SensorPolarityState
{
	SPOL_White_hot = 0,
	SPOL_Black_hot = 1,
};

enum SensorTrackState
{
	TS_White = 0,
	TS_Black = 1,
};

enum SensorTrackModeState
{
	TMS_Off = 0,
	TMS_Force_Correlate = 1,
	TMS_Scene = 2,
	TMS_Target = 3,
	TMS_Ship = 4,
	TMS_Custom_1 = 5,
	TMS_Custom_2 = 6,
	TMS_Custom_3 = 7,
};

enum SensorResponseType
{
	SRT_Normal = 0,
	SRT_Extended = 1,
};

enum MirrorModeState
{
	MM_None = 0,
	MM_Horizontal = 1,
	MM_Vertical = 2,
	MM_Horizontal_And_Vertical = 3,
};

enum PixelReplicationState
{
	PRM_None = 0,
	PRM_1x2 = 1,
	PRM_2x1 = 2,
	PRM_2x2 = 3,
	PRM_Custom_1 = 4,
	PRM_Custom_2 = 5,
	PRM_Custom_3 = 6,
	PRM_Custom_4 = 7,
};

enum ProjectionType
{
	PROJ_Perspective = 0,
	PROJ_Orthographic_Parallel = 1,
};

enum ReorderState
{
	REORDER_No_Reorder = 0,
	REORDER_Bring_To_Top = 1,
};

enum HATHOTRequestType
{
	HHRqT_HAT = 0,
	HHRqT_HOT = 1,
	HHRqT_Extended = 2,
};

enum HATHOTResponseType
{
	HHRT_HAT = 0,
	HHRT_HOT = 1,
};

enum LOSRequestType
{
	LOSRT_Basic = 0,
	LOSRT_Extended = 1,
};

enum GeodeticEntityCS
{
	GECS_Geodetic = 0,
	GECS_Entity = 1,
};

enum EarthRefModelType
{
	ERM_WGS_84 = 0,
	ERM_Host_Defined = 1,
};

//===------------------------------===//
// IG Control
// The IG Control packet is used to control the IG operational ...
//===------------------------------===//
class IG_Control : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 24,
		PACKET_ID = 1
	};
	IG_Control() :
		Packet_ID( static_cast<unsigned char>(1) )
		, 		Packet_Size( static_cast<unsigned char>(24) )
		, 		Major_Version( static_cast<unsigned char>(3) )
		, 		Database_Number( static_cast<char>(0) )
		, 		ByteSwap_Magic_Number( static_cast<unsigned short>(32768) )
	{
		set_IG_Mode( static_cast<IGModeState>(0) );
		set_Timestamp_Valid( static_cast<TimestampState>(0) );
		set_Extra_Interpolation_mode( static_cast<GenericBoolState>(0) );
		set_Minor_Version( static_cast<unsigned char>(3) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned char get_Major_Version() const
	{
		return static_cast<unsigned char>(Major_Version);
	}
	char get_Database_Number() const
	{
		return static_cast<char>(Database_Number);
	}
	void set_Database_Number( char value )
	{
		Database_Number = static_cast<char>( value );
	}
	IGModeState get_IG_Mode() const
	{
		return static_cast<IGModeState>( extractBits<unsigned int, 0, 2>( (unsigned int)BitsGroup_0 ) );
	}
	void set_IG_Mode( IGModeState value )
	{
		setBits<unsigned char,0,2>( BitsGroup_0, value );
	}
	TimestampState get_Timestamp_Valid() const
	{
		return static_cast<TimestampState>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Timestamp_Valid( TimestampState value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Extra_Interpolation_mode() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 3, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Extra_Interpolation_mode( GenericBoolState value )
	{
		setBits<unsigned char,3,1>( BitsGroup_0, value );
	}
	unsigned char get_Minor_Version() const
	{
		return static_cast<unsigned char>( extractBits<unsigned int, 4, 4>( (unsigned int)BitsGroup_0 ) );
	}
	unsigned short get_ByteSwap_Magic_Number() const
	{
		return static_cast<unsigned short>(ByteSwap_Magic_Number);
	}
	unsigned int get_Host_Frame_Number() const
	{
		return static_cast<unsigned int>(Host_Frame_Number);
	}
	void set_Host_Frame_Number( unsigned int value )
	{
		Host_Frame_Number = static_cast<unsigned int>( value );
	}
	unsigned int get_Timestamp() const
	{
		return static_cast<unsigned int>(Timestamp);
	}
	void set_Timestamp( unsigned int value )
	{
		Timestamp = static_cast<unsigned int>( value );
	}
	unsigned int get_Last_IG_Frame_Number() const
	{
		return static_cast<unsigned int>(Last_IG_Frame_Number);
	}
	void set_Last_IG_Frame_Number( unsigned int value )
	{
		Last_IG_Frame_Number = static_cast<unsigned int>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
	void set_Major_Version( unsigned char value )
	{
		Major_Version = static_cast<unsigned char>( value );
	}
	void set_Minor_Version( unsigned char value )
	{
		setBits<unsigned char,4,4>( BitsGroup_0, value );
	}
	void set_ByteSwap_Magic_Number( unsigned short value )
	{
		ByteSwap_Magic_Number = static_cast<unsigned short>( value );
	}
protected:
	// Default value: 1
	unsigned char Packet_ID;

	// Default value: 24
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 3
	unsigned char Major_Version;

	// Default value: 0
	char Database_Number;

	// Bits are for:
		// IG Mode (2 bits) (Default: 0)
		// Timestamp Valid (1 bits) (Default: 0)
		// Extra/Interpolation mode (1 bits) (Default: 0)
		// Minor Version (4 bits) (Default: 3)
	unsigned char BitsGroup_0;

	char Reserved_0;

	// Default value: 32768
	unsigned short ByteSwap_Magic_Number;

	unsigned int Host_Frame_Number;

	// Units: 10 microseconds
	unsigned int Timestamp;

	unsigned int Last_IG_Frame_Number;

	int Reserved_1;

};

//===------------------------------===//
// Entity Control
// The Entity Control packet is used to control position...
//===------------------------------===//
class Entity_Control : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 48,
		PACKET_ID = 2
	};
	Entity_Control() :
		Packet_ID( static_cast<unsigned char>(2) )
		, 		Packet_Size( static_cast<unsigned char>(48) )
		, 		Entity_ID( static_cast<unsigned short>(0) )
		, 		Alpha( static_cast<unsigned char>(255) )
		, 		Entity_Type( static_cast<unsigned short>(0) )
		, 		Parent_ID( static_cast<unsigned short>(0) )
		, 		Roll( static_cast<float>(0.0f) )
		, 		Pitch( static_cast<float>(0.0f) )
		, 		Yaw( static_cast<float>(0.0f) )
		, 		Latitude_X_Offset( static_cast<double>(0.0) )
		, 		Longitude_Y_Offset( static_cast<double>(0.0) )
		, 		Altitude_Z_Offset( static_cast<double>(0.0) )
	{
		set_Entity_State( static_cast<EntityState>(0) );
		set_Attach_State( static_cast<AttachState>(1) );
		set_Collision_Detection_Enable( static_cast<GenericBoolState>(0) );
		set_Inherit_Alpha( static_cast<InheritAlphaState>(0) );
		set_Ground_Ocean_Clamp( static_cast<ClampState>(0) );
		set_Animation_Direction( static_cast<char>(0) );
		set_Animation_Loop_Mode( static_cast<char>(0) );
		set_Animation_State( static_cast<AnimState>(0) );
		set_Linear_ExtInt_Enable( static_cast<GenericBoolState>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		// Using sequential read. Set the attribute binCopy="true" for the packet to force memcpy instead
		DataPtrReader ptr(data,s);
		size_t c = 0;
		Packet_ID = ptr.get<unsigned char>(); c += sizeof(unsigned char);
		Packet_Size = ptr.get<unsigned char>(); c += sizeof(unsigned char);
		Entity_ID = ptr.get<unsigned short>(); c += sizeof(unsigned short);
		BitsGroup_0 = ptr.get<unsigned char>(); c+= sizeof(unsigned char);
		BitsGroup_1 = ptr.get<unsigned char>(); c+= sizeof(unsigned char);
		Alpha = ptr.get<unsigned char>(); c += sizeof(unsigned char);
		Entity_Type = ptr.get<unsigned short>(); c += sizeof(unsigned short);
		Parent_ID = ptr.get<unsigned short>(); c += sizeof(unsigned short);
		Roll = ptr.get<float>(); c += sizeof(float);
		Pitch = ptr.get<float>(); c += sizeof(float);
		Yaw = ptr.get<float>(); c += sizeof(float);
		Latitude_X_Offset = ptr.get<double>(); c += sizeof(double);
		Longitude_Y_Offset = ptr.get<double>(); c += sizeof(double);
		Altitude_Z_Offset = ptr.get<double>(); c += sizeof(double);
		return c;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		// Using sequential writing. Set the attribute binCopy="true" for the packet to force memcpy instead
		DataPtrWriter ptr(data,s);
		size_t c = 0;
		ptr.set<unsigned char>(Packet_ID); c += sizeof(unsigned char);
		ptr.set<unsigned char>(Packet_Size); c += sizeof(unsigned char);
		ptr.set<unsigned short>(Entity_ID); c += sizeof(unsigned short);
		ptr.set<unsigned char>(BitsGroup_0); c+= sizeof(unsigned char);
		ptr.set<unsigned char>(BitsGroup_1); c+= sizeof(unsigned char);
		ptr.set<unsigned char>(Alpha); c += sizeof(unsigned char);
		ptr.set<unsigned short>(Entity_Type); c += sizeof(unsigned short);
		ptr.set<unsigned short>(Parent_ID); c += sizeof(unsigned short);
		ptr.set<float>(Roll); c += sizeof(float);
		ptr.set<float>(Pitch); c += sizeof(float);
		ptr.set<float>(Yaw); c += sizeof(float);
		ptr.set<double>(Latitude_X_Offset); c += sizeof(double);
		ptr.set<double>(Longitude_Y_Offset); c += sizeof(double);
		ptr.set<double>(Altitude_Z_Offset); c += sizeof(double);
		return c;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_Entity_ID() const
	{
		return static_cast<unsigned short>(Entity_ID);
	}
	void set_Entity_ID( unsigned short value )
	{
		Entity_ID = static_cast<unsigned short>( value );
	}
	EntityState get_Entity_State() const
	{
		return static_cast<EntityState>( extractBits<unsigned int, 0, 2>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Entity_State( EntityState value )
	{
		setBits<unsigned char,0,2>( BitsGroup_0, value );
	}
	AttachState get_Attach_State() const
	{
		return static_cast<AttachState>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Attach_State( AttachState value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Collision_Detection_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 3, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Collision_Detection_Enable( GenericBoolState value )
	{
		setBits<unsigned char,3,1>( BitsGroup_0, value );
	}
	InheritAlphaState get_Inherit_Alpha() const
	{
		return static_cast<InheritAlphaState>( extractBits<unsigned int, 4, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Inherit_Alpha( InheritAlphaState value )
	{
		setBits<unsigned char,4,1>( BitsGroup_0, value );
	}
	ClampState get_Ground_Ocean_Clamp() const
	{
		return static_cast<ClampState>( extractBits<unsigned int, 5, 2>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Ground_Ocean_Clamp( ClampState value )
	{
		setBits<unsigned char,5,2>( BitsGroup_0, value );
	}
	char get_Animation_Direction() const
	{
		return static_cast<char>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_1 ) );
	}
	void set_Animation_Direction( char value )
	{
		setBits<unsigned char,0,1>( BitsGroup_1, value );
	}
	char get_Animation_Loop_Mode() const
	{
		return static_cast<char>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_1 ) );
	}
	void set_Animation_Loop_Mode( char value )
	{
		setBits<unsigned char,1,1>( BitsGroup_1, value );
	}
	AnimState get_Animation_State() const
	{
		return static_cast<AnimState>( extractBits<unsigned int, 2, 2>( (unsigned int)BitsGroup_1 ) );
	}
	void set_Animation_State( AnimState value )
	{
		setBits<unsigned char,2,2>( BitsGroup_1, value );
	}
	GenericBoolState get_Linear_ExtInt_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 4, 1>( (unsigned int)BitsGroup_1 ) );
	}
	void set_Linear_ExtInt_Enable( GenericBoolState value )
	{
		setBits<unsigned char,4,1>( BitsGroup_1, value );
	}
	unsigned char get_Alpha() const
	{
		return static_cast<unsigned char>(Alpha);
	}
	void set_Alpha( unsigned char value )
	{
		Alpha = static_cast<unsigned char>( value );
	}
	unsigned short get_Entity_Type() const
	{
		return static_cast<unsigned short>(Entity_Type);
	}
	void set_Entity_Type( unsigned short value )
	{
		Entity_Type = static_cast<unsigned short>( value );
	}
	unsigned short get_Parent_ID() const
	{
		return static_cast<unsigned short>(Parent_ID);
	}
	void set_Parent_ID( unsigned short value )
	{
		Parent_ID = static_cast<unsigned short>( value );
	}
	float get_Roll() const
	{
		return static_cast<float>(Roll);
	}
	void set_Roll( float value )
	{
		Roll = static_cast<float>( value );
	}
	float get_Pitch() const
	{
		return static_cast<float>(Pitch);
	}
	void set_Pitch( float value )
	{
		Pitch = static_cast<float>( value );
	}
	float get_Yaw() const
	{
		return static_cast<float>(Yaw);
	}
	void set_Yaw( float value )
	{
		Yaw = static_cast<float>( value );
	}
	double get_Latitude_X_Offset() const
	{
		return static_cast<double>(Latitude_X_Offset);
	}
	void set_Latitude_X_Offset( double value )
	{
		Latitude_X_Offset = static_cast<double>( value );
	}
	double get_Longitude_Y_Offset() const
	{
		return static_cast<double>(Longitude_Y_Offset);
	}
	void set_Longitude_Y_Offset( double value )
	{
		Longitude_Y_Offset = static_cast<double>( value );
	}
	double get_Altitude_Z_Offset() const
	{
		return static_cast<double>(Altitude_Z_Offset);
	}
	void set_Altitude_Z_Offset( double value )
	{
		Altitude_Z_Offset = static_cast<double>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 2
	unsigned char Packet_ID;

	// Default value: 48
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short Entity_ID;

	// Bits are for:
		// Entity State (2 bits) (Default: 0)
		// Attach State (1 bits) (Default: 1)
		// Collision Detection Enable (1 bits) (Default: 0)
		// Inherit Alpha (1 bits) (Default: 0)
		// Ground/Ocean Clamp (2 bits) (Default: 0)
		//  (1 bits) (Default: )
	unsigned char BitsGroup_0;

	// Bits are for:
		// Animation Direction (1 bits) (Default: 0)
		// Animation Loop Mode (1 bits) (Default: 0)
		// Animation State (2 bits) (Default: 0)
		// Linear ExtInt Enable (1 bits) (Default: 0)
		//  (3 bits) (Default: )
	unsigned char BitsGroup_1;

	// Default value: 255
	unsigned char Alpha;

	// Default value: 0
	unsigned short Entity_Type;

	// Default value: 0
	unsigned short Parent_ID;

	// Default value: 0.0f
	float Roll;

	// Default value: 0.0f
	float Pitch;

	// Default value: 0.0f
	float Yaw;

	// Default value: 0.0
	double Latitude_X_Offset;

	// Default value: 0.0
	double Longitude_Y_Offset;

	// Default value: 0.0
	double Altitude_Z_Offset;

};

//===------------------------------===//
// Conformal Clamped Entity Control
// The Conformal Clamped Entity Control parameter is ...
//===------------------------------===//
class Conformal_Clamped_Entity_Control : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 24,
		PACKET_ID = 3
	};
	Conformal_Clamped_Entity_Control() :
		Packet_ID( static_cast<unsigned char>(3) )
		, 		Packet_Size( static_cast<unsigned char>(24) )
		, 		Entity_ID( static_cast<unsigned short>(0) )
		, 		Yaw( static_cast<float>(0.0f) )
		, 		Latitude( static_cast<double>(0.0) )
		, 		Longitude( static_cast<double>(0.0) )
	{
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_Entity_ID() const
	{
		return static_cast<unsigned short>(Entity_ID);
	}
	void set_Entity_ID( unsigned short value )
	{
		Entity_ID = static_cast<unsigned short>( value );
	}
	float get_Yaw() const
	{
		return static_cast<float>(Yaw);
	}
	void set_Yaw( float value )
	{
		Yaw = static_cast<float>( value );
	}
	double get_Latitude() const
	{
		return static_cast<double>(Latitude);
	}
	void set_Latitude( double value )
	{
		Latitude = static_cast<double>( value );
	}
	double get_Longitude() const
	{
		return static_cast<double>(Longitude);
	}
	void set_Longitude( double value )
	{
		Longitude = static_cast<double>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 3
	unsigned char Packet_ID;

	// Default value: 24
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short Entity_ID;

	// Default value: 0.0f
	float Yaw;

	// Default value: 0.0
	double Latitude;

	// Default value: 0.0
	double Longitude;

};

//===------------------------------===//
// Component Control
// 
//===------------------------------===//
class Component_Control : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 32,
		PACKET_ID = 4
	};
	Component_Control() :
		Packet_ID( static_cast<unsigned char>(4) )
		, 		Packet_Size( static_cast<unsigned char>(32) )
		, 		Component_ID( static_cast<unsigned short>(0) )
		, 		Instance_ID( static_cast<unsigned short>(0) )
		, 		Component_State( static_cast<char>(0) )
		, 		Component_Data_1( static_cast<unsigned int>(0) )
		, 		Component_Data_2( static_cast<unsigned int>(0) )
		, 		Component_Data_3( static_cast<unsigned int>(0) )
		, 		Component_Data_4( static_cast<unsigned int>(0) )
		, 		Component_Data_5( static_cast<unsigned int>(0) )
		, 		Component_Data_6( static_cast<unsigned int>(0) )
	{
		set_Component_Class( static_cast<char>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_Component_ID() const
	{
		return static_cast<unsigned short>(Component_ID);
	}
	void set_Component_ID( unsigned short value )
	{
		Component_ID = static_cast<unsigned short>( value );
	}
	unsigned short get_Instance_ID() const
	{
		return static_cast<unsigned short>(Instance_ID);
	}
	void set_Instance_ID( unsigned short value )
	{
		Instance_ID = static_cast<unsigned short>( value );
	}
	char get_Component_Class() const
	{
		return static_cast<char>( extractBits<unsigned int, 0, 6>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Component_Class( char value )
	{
		setBits<unsigned char,0,6>( BitsGroup_0, value );
	}
	char get_Component_State() const
	{
		return static_cast<char>(Component_State);
	}
	void set_Component_State( char value )
	{
		Component_State = static_cast<char>( value );
	}
	unsigned int get_Component_Data_1() const
	{
		return static_cast<unsigned int>(Component_Data_1);
	}
	void set_Component_Data_1( unsigned int value )
	{
		Component_Data_1 = static_cast<unsigned int>( value );
	}
	unsigned int get_Component_Data_2() const
	{
		return static_cast<unsigned int>(Component_Data_2);
	}
	void set_Component_Data_2( unsigned int value )
	{
		Component_Data_2 = static_cast<unsigned int>( value );
	}
	unsigned int get_Component_Data_3() const
	{
		return static_cast<unsigned int>(Component_Data_3);
	}
	void set_Component_Data_3( unsigned int value )
	{
		Component_Data_3 = static_cast<unsigned int>( value );
	}
	unsigned int get_Component_Data_4() const
	{
		return static_cast<unsigned int>(Component_Data_4);
	}
	void set_Component_Data_4( unsigned int value )
	{
		Component_Data_4 = static_cast<unsigned int>( value );
	}
	unsigned int get_Component_Data_5() const
	{
		return static_cast<unsigned int>(Component_Data_5);
	}
	void set_Component_Data_5( unsigned int value )
	{
		Component_Data_5 = static_cast<unsigned int>( value );
	}
	unsigned int get_Component_Data_6() const
	{
		return static_cast<unsigned int>(Component_Data_6);
	}
	void set_Component_Data_6( unsigned int value )
	{
		Component_Data_6 = static_cast<unsigned int>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 4
	unsigned char Packet_ID;

	// Default value: 32
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short Component_ID;

	// Default value: 0
	unsigned short Instance_ID;

	// Bits are for:
		// Component Class (6 bits) (Default: 0)
		//  (2 bits) (Default: )
	unsigned char BitsGroup_0;

	// Default value: 0
	char Component_State;

	// Default value: 0
	unsigned int Component_Data_1;

	// Default value: 0
	unsigned int Component_Data_2;

	// Default value: 0
	unsigned int Component_Data_3;

	// Default value: 0
	unsigned int Component_Data_4;

	// Default value: 0
	unsigned int Component_Data_5;

	// Default value: 0
	unsigned int Component_Data_6;

};

//===------------------------------===//
// Articulated Part Control
// 
//===------------------------------===//
class Articulated_Part_Control : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 32,
		PACKET_ID = 6
	};
	Articulated_Part_Control() :
		Packet_ID( static_cast<unsigned char>(6) )
		, 		Packet_Size( static_cast<unsigned char>(32) )
		, 		Entity_ID( static_cast<unsigned short>(0) )
		, 		Articulated_Part_ID( static_cast<unsigned char>(0) )
		, 		X_Offset( static_cast<float>(0.0) )
		, 		Y_Offset( static_cast<float>(0.0) )
		, 		Z_Offset( static_cast<float>(0.0) )
		, 		Roll( static_cast<float>(0.0) )
		, 		Pitch( static_cast<float>(0.0) )
		, 		Yaw( static_cast<float>(0.0) )
	{
		set_Articulated_Part_Enable( static_cast<GenericBoolState>(1) );
		set_X_Offset_Enable( static_cast<GenericBoolState>(1) );
		set_Y_Offset_Enable( static_cast<GenericBoolState>(1) );
		set_Z_Offset_Enable( static_cast<GenericBoolState>(1) );
		set_Roll_Enable( static_cast<GenericBoolState>(1) );
		set_Pitch_Enable( static_cast<GenericBoolState>(1) );
		set_Yaw_Enable( static_cast<GenericBoolState>(1) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_Entity_ID() const
	{
		return static_cast<unsigned short>(Entity_ID);
	}
	void set_Entity_ID( unsigned short value )
	{
		Entity_ID = static_cast<unsigned short>( value );
	}
	unsigned char get_Articulated_Part_ID() const
	{
		return static_cast<unsigned char>(Articulated_Part_ID);
	}
	void set_Articulated_Part_ID( unsigned char value )
	{
		Articulated_Part_ID = static_cast<unsigned char>( value );
	}
	GenericBoolState get_Articulated_Part_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Articulated_Part_Enable( GenericBoolState value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	GenericBoolState get_X_Offset_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_X_Offset_Enable( GenericBoolState value )
	{
		setBits<unsigned char,1,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Y_Offset_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Y_Offset_Enable( GenericBoolState value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Z_Offset_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 3, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Z_Offset_Enable( GenericBoolState value )
	{
		setBits<unsigned char,3,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Roll_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 4, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Roll_Enable( GenericBoolState value )
	{
		setBits<unsigned char,4,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Pitch_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 5, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Pitch_Enable( GenericBoolState value )
	{
		setBits<unsigned char,5,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Yaw_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 6, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Yaw_Enable( GenericBoolState value )
	{
		setBits<unsigned char,6,1>( BitsGroup_0, value );
	}
	float get_X_Offset() const
	{
		return static_cast<float>(X_Offset);
	}
	void set_X_Offset( float value )
	{
		X_Offset = static_cast<float>( value );
	}
	float get_Y_Offset() const
	{
		return static_cast<float>(Y_Offset);
	}
	void set_Y_Offset( float value )
	{
		Y_Offset = static_cast<float>( value );
	}
	float get_Z_Offset() const
	{
		return static_cast<float>(Z_Offset);
	}
	void set_Z_Offset( float value )
	{
		Z_Offset = static_cast<float>( value );
	}
	float get_Roll() const
	{
		return static_cast<float>(Roll);
	}
	void set_Roll( float value )
	{
		Roll = static_cast<float>( value );
	}
	float get_Pitch() const
	{
		return static_cast<float>(Pitch);
	}
	void set_Pitch( float value )
	{
		Pitch = static_cast<float>( value );
	}
	float get_Yaw() const
	{
		return static_cast<float>(Yaw);
	}
	void set_Yaw( float value )
	{
		Yaw = static_cast<float>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 6
	unsigned char Packet_ID;

	// Default value: 32
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short Entity_ID;

	// Default value: 0
	unsigned char Articulated_Part_ID;

	// Bits are for:
		// Articulated Part Enable (1 bits) (Default: 1)
		// X Offset Enable (1 bits) (Default: 1)
		// Y Offset Enable (1 bits) (Default: 1)
		// Z Offset Enable (1 bits) (Default: 1)
		// Roll Enable (1 bits) (Default: 1)
		// Pitch Enable (1 bits) (Default: 1)
		// Yaw Enable (1 bits) (Default: 1)
		//  (1 bits) (Default: )
	unsigned char BitsGroup_0;

	short Reserved_0;

	// Default value: 0.0
	float X_Offset;

	// Default value: 0.0
	float Y_Offset;

	// Default value: 0.0
	float Z_Offset;

	// Default value: 0.0
	float Roll;

	// Default value: 0.0
	float Pitch;

	// Default value: 0.0
	float Yaw;

};

//===------------------------------===//
// Short Articulated Part Control
// 
//===------------------------------===//
class Short_Articulated_Part_Control : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 16,
		PACKET_ID = 7
	};
	Short_Articulated_Part_Control() :
		Packet_ID( static_cast<unsigned char>(7) )
		, 		Packet_Size( static_cast<unsigned char>(16) )
		, 		Entity_ID( static_cast<unsigned short>(0) )
		, 		Articulated_Part_ID_1( static_cast<unsigned char>(0) )
		, 		Articulated_Part_ID_2( static_cast<unsigned char>(0) )
		, 		DOF_1( static_cast<float>(0.0f) )
		, 		DOF_2( static_cast<float>(0.0f) )
	{
		set_DOF_Select_1( static_cast<DOFSelectState>(0) );
		set_DOF_Select_2( static_cast<DOFSelectState>(0) );
		set_Articulated_Part_Enable_1( static_cast<GenericBoolState>(1) );
		set_Articulated_Part_Enable_2( static_cast<GenericBoolState>(1) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_Entity_ID() const
	{
		return static_cast<unsigned short>(Entity_ID);
	}
	void set_Entity_ID( unsigned short value )
	{
		Entity_ID = static_cast<unsigned short>( value );
	}
	unsigned char get_Articulated_Part_ID_1() const
	{
		return static_cast<unsigned char>(Articulated_Part_ID_1);
	}
	void set_Articulated_Part_ID_1( unsigned char value )
	{
		Articulated_Part_ID_1 = static_cast<unsigned char>( value );
	}
	unsigned char get_Articulated_Part_ID_2() const
	{
		return static_cast<unsigned char>(Articulated_Part_ID_2);
	}
	void set_Articulated_Part_ID_2( unsigned char value )
	{
		Articulated_Part_ID_2 = static_cast<unsigned char>( value );
	}
	DOFSelectState get_DOF_Select_1() const
	{
		return static_cast<DOFSelectState>( extractBits<unsigned int, 0, 3>( (unsigned int)BitsGroup_0 ) );
	}
	void set_DOF_Select_1( DOFSelectState value )
	{
		setBits<unsigned char,0,3>( BitsGroup_0, value );
	}
	DOFSelectState get_DOF_Select_2() const
	{
		return static_cast<DOFSelectState>( extractBits<unsigned int, 3, 3>( (unsigned int)BitsGroup_0 ) );
	}
	void set_DOF_Select_2( DOFSelectState value )
	{
		setBits<unsigned char,3,3>( BitsGroup_0, value );
	}
	GenericBoolState get_Articulated_Part_Enable_1() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 6, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Articulated_Part_Enable_1( GenericBoolState value )
	{
		setBits<unsigned char,6,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Articulated_Part_Enable_2() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 7, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Articulated_Part_Enable_2( GenericBoolState value )
	{
		setBits<unsigned char,7,1>( BitsGroup_0, value );
	}
	float get_DOF_1() const
	{
		return static_cast<float>(DOF_1);
	}
	void set_DOF_1( float value )
	{
		DOF_1 = static_cast<float>( value );
	}
	float get_DOF_2() const
	{
		return static_cast<float>(DOF_2);
	}
	void set_DOF_2( float value )
	{
		DOF_2 = static_cast<float>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 7
	unsigned char Packet_ID;

	// Default value: 16
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short Entity_ID;

	// Default value: 0
	unsigned char Articulated_Part_ID_1;

	// Default value: 0
	unsigned char Articulated_Part_ID_2;

	// Bits are for:
		// DOF Select 1 (3 bits) (Default: 0)
		// DOF Select 2 (3 bits) (Default: 0)
		// Articulated Part Enable 1 (1 bits) (Default: 1)
		// Articulated Part Enable 2 (1 bits) (Default: 1)
	unsigned char BitsGroup_0;

	char Reserved_0;

	// Default value: 0.0f
	float DOF_1;

	// Default value: 0.0f
	float DOF_2;

};

//===------------------------------===//
// Rate Control
// 
//===------------------------------===//
class Rate_Control : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 32,
		PACKET_ID = 8
	};
	Rate_Control() :
		Packet_ID( static_cast<unsigned char>(8) )
		, 		Packet_Size( static_cast<unsigned char>(32) )
		, 		Entity_ID( static_cast<unsigned short>(0) )
		, 		Articulated_Part_ID( static_cast<unsigned char>(0) )
		, 		X_Linear_Rate( static_cast<float>(0.0f) )
		, 		Y_Linear_Rate( static_cast<float>(0.0f) )
		, 		Z_Linear_Rate( static_cast<float>(0.0f) )
		, 		Roll_Angular_Rate( static_cast<float>(0.0f) )
		, 		Pitch_Angular_Rate( static_cast<float>(0.0f) )
		, 		Yaw_Angular_Rate( static_cast<float>(0.0f) )
	{
		set_Apply_to_Articulated_Part( static_cast<GenericBoolState>(0) );
		set_Coordinate_System( static_cast<RateControlCSState>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_Entity_ID() const
	{
		return static_cast<unsigned short>(Entity_ID);
	}
	void set_Entity_ID( unsigned short value )
	{
		Entity_ID = static_cast<unsigned short>( value );
	}
	unsigned char get_Articulated_Part_ID() const
	{
		return static_cast<unsigned char>(Articulated_Part_ID);
	}
	void set_Articulated_Part_ID( unsigned char value )
	{
		Articulated_Part_ID = static_cast<unsigned char>( value );
	}
	GenericBoolState get_Apply_to_Articulated_Part() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Apply_to_Articulated_Part( GenericBoolState value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	RateControlCSState get_Coordinate_System() const
	{
		return static_cast<RateControlCSState>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Coordinate_System( RateControlCSState value )
	{
		setBits<unsigned char,1,1>( BitsGroup_0, value );
	}
	float get_X_Linear_Rate() const
	{
		return static_cast<float>(X_Linear_Rate);
	}
	void set_X_Linear_Rate( float value )
	{
		X_Linear_Rate = static_cast<float>( value );
	}
	float get_Y_Linear_Rate() const
	{
		return static_cast<float>(Y_Linear_Rate);
	}
	void set_Y_Linear_Rate( float value )
	{
		Y_Linear_Rate = static_cast<float>( value );
	}
	float get_Z_Linear_Rate() const
	{
		return static_cast<float>(Z_Linear_Rate);
	}
	void set_Z_Linear_Rate( float value )
	{
		Z_Linear_Rate = static_cast<float>( value );
	}
	float get_Roll_Angular_Rate() const
	{
		return static_cast<float>(Roll_Angular_Rate);
	}
	void set_Roll_Angular_Rate( float value )
	{
		Roll_Angular_Rate = static_cast<float>( value );
	}
	float get_Pitch_Angular_Rate() const
	{
		return static_cast<float>(Pitch_Angular_Rate);
	}
	void set_Pitch_Angular_Rate( float value )
	{
		Pitch_Angular_Rate = static_cast<float>( value );
	}
	float get_Yaw_Angular_Rate() const
	{
		return static_cast<float>(Yaw_Angular_Rate);
	}
	void set_Yaw_Angular_Rate( float value )
	{
		Yaw_Angular_Rate = static_cast<float>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 8
	unsigned char Packet_ID;

	// Default value: 32
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short Entity_ID;

	// Default value: 0
	unsigned char Articulated_Part_ID;

	// Bits are for:
		// Apply to Articulated Part (1 bits) (Default: 0)
		// Coordinate System (1 bits) (Default: 0)
	unsigned char BitsGroup_0;

	short Reserved_0;

	// Default value: 0.0f
	float X_Linear_Rate;

	// Default value: 0.0f
	float Y_Linear_Rate;

	// Default value: 0.0f
	float Z_Linear_Rate;

	// Default value: 0.0f
	float Roll_Angular_Rate;

	// Default value: 0.0f
	float Pitch_Angular_Rate;

	// Default value: 0.0f
	float Yaw_Angular_Rate;

};

//===------------------------------===//
// Celestial Sphere Control
// 
//===------------------------------===//
class Celestial_Sphere_Control : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 16,
		PACKET_ID = 9
	};
	Celestial_Sphere_Control() :
		Packet_ID( static_cast<unsigned char>(9) )
		, 		Packet_Size( static_cast<unsigned char>(16) )
		, 		Hour( static_cast<unsigned char>(0) )
		, 		Minute( static_cast<unsigned char>(0) )
		, 		Date( static_cast<unsigned int>(0) )
		, 		Star_Field_Intensity( static_cast<float>(0.0f) )
	{
		set_Ephemeris_Model_Enable( static_cast<GenericBoolState>(1) );
		set_Sun_Enable( static_cast<GenericBoolState>(0) );
		set_Moon_Enable( static_cast<GenericBoolState>(0) );
		set_Star_Field_Enable( static_cast<GenericBoolState>(0) );
		set_Date_Time_Valid( static_cast<GenericValidState>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned char get_Hour() const
	{
		return static_cast<unsigned char>(Hour);
	}
	void set_Hour( unsigned char value )
	{
		Hour = static_cast<unsigned char>( value );
	}
	unsigned char get_Minute() const
	{
		return static_cast<unsigned char>(Minute);
	}
	void set_Minute( unsigned char value )
	{
		Minute = static_cast<unsigned char>( value );
	}
	GenericBoolState get_Ephemeris_Model_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Ephemeris_Model_Enable( GenericBoolState value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Sun_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Sun_Enable( GenericBoolState value )
	{
		setBits<unsigned char,1,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Moon_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Moon_Enable( GenericBoolState value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Star_Field_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 3, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Star_Field_Enable( GenericBoolState value )
	{
		setBits<unsigned char,3,1>( BitsGroup_0, value );
	}
	GenericValidState get_Date_Time_Valid() const
	{
		return static_cast<GenericValidState>( extractBits<unsigned int, 4, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Date_Time_Valid( GenericValidState value )
	{
		setBits<unsigned char,4,1>( BitsGroup_0, value );
	}
	unsigned int get_Date() const
	{
		return static_cast<unsigned int>(Date);
	}
	void set_Date( unsigned int value )
	{
		Date = static_cast<unsigned int>( value );
	}
	float get_Star_Field_Intensity() const
	{
		return static_cast<float>(Star_Field_Intensity);
	}
	void set_Star_Field_Intensity( float value )
	{
		Star_Field_Intensity = static_cast<float>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 9
	unsigned char Packet_ID;

	// Default value: 16
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned char Hour;

	// Default value: 0
	unsigned char Minute;

	// Bits are for:
		// Ephemeris Model Enable (1 bits) (Default: 1)
		// Sun Enable (1 bits) (Default: 0)
		// Moon Enable (1 bits) (Default: 0)
		// Star Field Enable (1 bits) (Default: 0)
		// Date/Time Valid (1 bits) (Default: 0)
		//  (3 bits) (Default: )
	unsigned char BitsGroup_0;

	short Reserved_0;

	char Reserved_1;

	// Default value: 0
	unsigned int Date;

	// Default value: 0.0f
	float Star_Field_Intensity;

};

//===------------------------------===//
// Atmosphere Control
// 
//===------------------------------===//
class Atmosphere_Control : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 32,
		PACKET_ID = 10
	};
	Atmosphere_Control() :
		Packet_ID( static_cast<unsigned char>(10) )
		, 		Packet_Size( static_cast<unsigned char>(32) )
	{
		set_Atmospheric_Model_Enable( static_cast<GenericBoolState>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	GenericBoolState get_Atmospheric_Model_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Atmospheric_Model_Enable( GenericBoolState value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	unsigned char get_Global_Humidity() const
	{
		return static_cast<unsigned char>(Global_Humidity);
	}
	void set_Global_Humidity( unsigned char value )
	{
		Global_Humidity = static_cast<unsigned char>( value );
	}
	float get_Global_Air_Temperature() const
	{
		return static_cast<float>(Global_Air_Temperature);
	}
	void set_Global_Air_Temperature( float value )
	{
		Global_Air_Temperature = static_cast<float>( value );
	}
	float get_Global_Visibility_Range() const
	{
		return static_cast<float>(Global_Visibility_Range);
	}
	void set_Global_Visibility_Range( float value )
	{
		Global_Visibility_Range = static_cast<float>( value );
	}
	float get_Global_Horizon_Wind_Speed() const
	{
		return static_cast<float>(Global_Horizon_Wind_Speed);
	}
	void set_Global_Horizon_Wind_Speed( float value )
	{
		Global_Horizon_Wind_Speed = static_cast<float>( value );
	}
	float get_Global_Vertical_Wind_Speed() const
	{
		return static_cast<float>(Global_Vertical_Wind_Speed);
	}
	void set_Global_Vertical_Wind_Speed( float value )
	{
		Global_Vertical_Wind_Speed = static_cast<float>( value );
	}
	float get_Global_Wind_Direction() const
	{
		return static_cast<float>(Global_Wind_Direction);
	}
	void set_Global_Wind_Direction( float value )
	{
		Global_Wind_Direction = static_cast<float>( value );
	}
	float get_Global_Barometric_Pressure() const
	{
		return static_cast<float>(Global_Barometric_Pressure);
	}
	void set_Global_Barometric_Pressure( float value )
	{
		Global_Barometric_Pressure = static_cast<float>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 10
	unsigned char Packet_ID;

	// Default value: 32
	// Units: bytes
	unsigned char Packet_Size;

	// Bits are for:
		// Atmospheric Model Enable (1 bits) (Default: 0)
		//  (7 bits) (Default: )
	unsigned char BitsGroup_0;

	unsigned char Global_Humidity;

	float Global_Air_Temperature;

	float Global_Visibility_Range;

	float Global_Horizon_Wind_Speed;

	float Global_Vertical_Wind_Speed;

	float Global_Wind_Direction;

	float Global_Barometric_Pressure;

	int Reserved_0;

};

//===------------------------------===//
// Weather Control
// 
//===------------------------------===//
class Weather_Control : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 56,
		PACKET_ID = 12
	};
	Weather_Control() :
		Packet_ID( static_cast<unsigned char>(12) )
		, 		Packet_Size( static_cast<unsigned char>(56) )
		, 		Layer_ID( static_cast<unsigned char>(0) )
		, 		Humidity( static_cast<unsigned char>(0) )
		, 		Air_Temperature( static_cast<float>(0.0f) )
		, 		Visiblity_Range( static_cast<float>(0.0f) )
		, 		Scud_Frequency( static_cast<float>(0.0f) )
		, 		Coverage( static_cast<float>(0.0f) )
		, 		Base_Elevation( static_cast<float>(0.0f) )
		, 		Thickness( static_cast<float>(0.0f) )
		, 		Transition_Band( static_cast<float>(0.0f) )
		, 		Horizontal_Wind_Speed( static_cast<float>(0.0f) )
		, 		Vertical_Wind_Speed( static_cast<float>(0.0f) )
		, 		Wind_Direction( static_cast<float>(0.0f) )
		, 		Barometric_Pressure( static_cast<float>(0.0f) )
		, 		Aerosol_Concentration( static_cast<float>(0.0f) )
	{
		set_Weather_Enable( static_cast<GenericBoolState>(0) );
		set_Scud_Enable( static_cast<GenericBoolState>(0) );
		set_Random_Winds_Enable( static_cast<GenericBoolState>(0) );
		set_Random_Lightning_Enable( static_cast<GenericBoolState>(0) );
		set_Cloud_Type( static_cast<WeatherCloudType>(0) );
		set_Scope( static_cast<WeatherScopeState>(0) );
		set_Severity( static_cast<char>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_Entity_Region_ID() const
	{
		return static_cast<unsigned short>(Entity_Region_ID);
	}
	void set_Entity_Region_ID( unsigned short value )
	{
		Entity_Region_ID = static_cast<unsigned short>( value );
	}
	// Use WeatherLayerState. Values 10-255 are defined by IG
	unsigned char get_Layer_ID() const
	{
		return static_cast<unsigned char>(Layer_ID);
	}
	void set_Layer_ID( unsigned char value )
	{
		Layer_ID = static_cast<unsigned char>( value );
	}
	unsigned char get_Humidity() const
	{
		return static_cast<unsigned char>(Humidity);
	}
	void set_Humidity( unsigned char value )
	{
		Humidity = static_cast<unsigned char>( value );
	}
	GenericBoolState get_Weather_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Weather_Enable( GenericBoolState value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Scud_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Scud_Enable( GenericBoolState value )
	{
		setBits<unsigned char,1,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Random_Winds_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Random_Winds_Enable( GenericBoolState value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Random_Lightning_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 3, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Random_Lightning_Enable( GenericBoolState value )
	{
		setBits<unsigned char,3,1>( BitsGroup_0, value );
	}
	WeatherCloudType get_Cloud_Type() const
	{
		return static_cast<WeatherCloudType>( extractBits<unsigned int, 4, 4>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Cloud_Type( WeatherCloudType value )
	{
		setBits<unsigned char,4,4>( BitsGroup_0, value );
	}
	WeatherScopeState get_Scope() const
	{
		return static_cast<WeatherScopeState>( extractBits<unsigned int, 0, 2>( (unsigned int)BitsGroup_1 ) );
	}
	void set_Scope( WeatherScopeState value )
	{
		setBits<unsigned char,0,2>( BitsGroup_1, value );
	}
	char get_Severity() const
	{
		return static_cast<char>( extractBits<unsigned int, 2, 3>( (unsigned int)BitsGroup_1 ) );
	}
	void set_Severity( char value )
	{
		setBits<unsigned char,2,3>( BitsGroup_1, value );
	}
	float get_Air_Temperature() const
	{
		return static_cast<float>(Air_Temperature);
	}
	void set_Air_Temperature( float value )
	{
		Air_Temperature = static_cast<float>( value );
	}
	float get_Visiblity_Range() const
	{
		return static_cast<float>(Visiblity_Range);
	}
	void set_Visiblity_Range( float value )
	{
		Visiblity_Range = static_cast<float>( value );
	}
	float get_Scud_Frequency() const
	{
		return static_cast<float>(Scud_Frequency);
	}
	void set_Scud_Frequency( float value )
	{
		Scud_Frequency = static_cast<float>( value );
	}
	float get_Coverage() const
	{
		return static_cast<float>(Coverage);
	}
	void set_Coverage( float value )
	{
		Coverage = static_cast<float>( value );
	}
	float get_Base_Elevation() const
	{
		return static_cast<float>(Base_Elevation);
	}
	void set_Base_Elevation( float value )
	{
		Base_Elevation = static_cast<float>( value );
	}
	float get_Thickness() const
	{
		return static_cast<float>(Thickness);
	}
	void set_Thickness( float value )
	{
		Thickness = static_cast<float>( value );
	}
	float get_Transition_Band() const
	{
		return static_cast<float>(Transition_Band);
	}
	void set_Transition_Band( float value )
	{
		Transition_Band = static_cast<float>( value );
	}
	float get_Horizontal_Wind_Speed() const
	{
		return static_cast<float>(Horizontal_Wind_Speed);
	}
	void set_Horizontal_Wind_Speed( float value )
	{
		Horizontal_Wind_Speed = static_cast<float>( value );
	}
	float get_Vertical_Wind_Speed() const
	{
		return static_cast<float>(Vertical_Wind_Speed);
	}
	void set_Vertical_Wind_Speed( float value )
	{
		Vertical_Wind_Speed = static_cast<float>( value );
	}
	float get_Wind_Direction() const
	{
		return static_cast<float>(Wind_Direction);
	}
	void set_Wind_Direction( float value )
	{
		Wind_Direction = static_cast<float>( value );
	}
	float get_Barometric_Pressure() const
	{
		return static_cast<float>(Barometric_Pressure);
	}
	void set_Barometric_Pressure( float value )
	{
		Barometric_Pressure = static_cast<float>( value );
	}
	float get_Aerosol_Concentration() const
	{
		return static_cast<float>(Aerosol_Concentration);
	}
	void set_Aerosol_Concentration( float value )
	{
		Aerosol_Concentration = static_cast<float>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 12
	unsigned char Packet_ID;

	// Default value: 56
	// Units: bytes
	unsigned char Packet_Size;

	unsigned short Entity_Region_ID;

	// Use WeatherLayerState. Values 10-255 are defined by IG
	// Default value: 0
	unsigned char Layer_ID;

	// Default value: 0
	unsigned char Humidity;

	// Bits are for:
		// Weather Enable (1 bits) (Default: 0)
		// Scud Enable (1 bits) (Default: 0)
		// Random Winds Enable (1 bits) (Default: 0)
		// Random Lightning Enable (1 bits) (Default: 0)
		// Cloud Type (4 bits) (Default: 0)
	unsigned char BitsGroup_0;

	// Bits are for:
		// Scope (2 bits) (Default: 0)
		// Severity (3 bits) (Default: 0)
		//  (3 bits) (Default: )
	unsigned char BitsGroup_1;

	// Default value: 0.0f
	float Air_Temperature;

	// Default value: 0.0f
	float Visiblity_Range;

	// Default value: 0.0f
	float Scud_Frequency;

	// Default value: 0.0f
	float Coverage;

	// Default value: 0.0f
	float Base_Elevation;

	// Default value: 0.0f
	float Thickness;

	// Default value: 0.0f
	float Transition_Band;

	// Default value: 0.0f
	float Horizontal_Wind_Speed;

	// Default value: 0.0f
	float Vertical_Wind_Speed;

	// Default value: 0.0f
	float Wind_Direction;

	// Default value: 0.0f
	float Barometric_Pressure;

	// Default value: 0.0f
	float Aerosol_Concentration;

};

//===------------------------------===//
// View Control
// 
//===------------------------------===//
class View_Control : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 32,
		PACKET_ID = 16
	};
	View_Control() :
		Packet_ID( static_cast<unsigned char>(16) )
		, 		Packet_Size( static_cast<unsigned char>(32) )
		, 		View_ID( static_cast<unsigned short>(0) )
		, 		Group_ID( static_cast<unsigned char>(0) )
		, 		Entity_ID( static_cast<unsigned short>(0) )
		, 		X_Offset( static_cast<float>(0.0f) )
		, 		Y_Offset( static_cast<float>(0.0f) )
		, 		Z_Offset( static_cast<float>(0.0f) )
		, 		Roll( static_cast<float>(0.0f) )
		, 		Pitch( static_cast<float>(0.0f) )
		, 		Yaw( static_cast<float>(0.0f) )
	{
		set_X_Offset_Enable( static_cast<GenericBoolState>(0) );
		set_Y_Offset_Enable( static_cast<GenericBoolState>(0) );
		set_Z_Offset_Enable( static_cast<GenericBoolState>(0) );
		set_Roll_Enable( static_cast<GenericBoolState>(0) );
		set_Pitch_Enable( static_cast<GenericBoolState>(0) );
		set_Yaw_Enable( static_cast<GenericBoolState>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_View_ID() const
	{
		return static_cast<unsigned short>(View_ID);
	}
	void set_View_ID( unsigned short value )
	{
		View_ID = static_cast<unsigned short>( value );
	}
	unsigned char get_Group_ID() const
	{
		return static_cast<unsigned char>(Group_ID);
	}
	void set_Group_ID( unsigned char value )
	{
		Group_ID = static_cast<unsigned char>( value );
	}
	GenericBoolState get_X_Offset_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_X_Offset_Enable( GenericBoolState value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Y_Offset_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Y_Offset_Enable( GenericBoolState value )
	{
		setBits<unsigned char,1,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Z_Offset_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Z_Offset_Enable( GenericBoolState value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Roll_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 3, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Roll_Enable( GenericBoolState value )
	{
		setBits<unsigned char,3,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Pitch_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 4, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Pitch_Enable( GenericBoolState value )
	{
		setBits<unsigned char,4,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Yaw_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 5, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Yaw_Enable( GenericBoolState value )
	{
		setBits<unsigned char,5,1>( BitsGroup_0, value );
	}
	unsigned short get_Entity_ID() const
	{
		return static_cast<unsigned short>(Entity_ID);
	}
	void set_Entity_ID( unsigned short value )
	{
		Entity_ID = static_cast<unsigned short>( value );
	}
	float get_X_Offset() const
	{
		return static_cast<float>(X_Offset);
	}
	void set_X_Offset( float value )
	{
		X_Offset = static_cast<float>( value );
	}
	float get_Y_Offset() const
	{
		return static_cast<float>(Y_Offset);
	}
	void set_Y_Offset( float value )
	{
		Y_Offset = static_cast<float>( value );
	}
	float get_Z_Offset() const
	{
		return static_cast<float>(Z_Offset);
	}
	void set_Z_Offset( float value )
	{
		Z_Offset = static_cast<float>( value );
	}
	float get_Roll() const
	{
		return static_cast<float>(Roll);
	}
	void set_Roll( float value )
	{
		Roll = static_cast<float>( value );
	}
	float get_Pitch() const
	{
		return static_cast<float>(Pitch);
	}
	void set_Pitch( float value )
	{
		Pitch = static_cast<float>( value );
	}
	float get_Yaw() const
	{
		return static_cast<float>(Yaw);
	}
	void set_Yaw( float value )
	{
		Yaw = static_cast<float>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 16
	unsigned char Packet_ID;

	// Default value: 32
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short View_ID;

	// Default value: 0
	unsigned char Group_ID;

	// Bits are for:
		// X Offset Enable (1 bits) (Default: 0)
		// Y Offset Enable (1 bits) (Default: 0)
		// Z Offset Enable (1 bits) (Default: 0)
		// Roll Enable (1 bits) (Default: 0)
		// Pitch Enable (1 bits) (Default: 0)
		// Yaw Enable (1 bits) (Default: 0)
		//  (2 bits) (Default: )
	unsigned char BitsGroup_0;

	// Default value: 0
	unsigned short Entity_ID;

	// Default value: 0.0f
	float X_Offset;

	// Default value: 0.0f
	float Y_Offset;

	// Default value: 0.0f
	float Z_Offset;

	// Default value: 0.0f
	float Roll;

	// Default value: 0.0f
	float Pitch;

	// Default value: 0.0f
	float Yaw;

};

//===------------------------------===//
// Sensor Control
// 
//===------------------------------===//
class Sensor_Control : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 24,
		PACKET_ID = 17
	};
	Sensor_Control() :
		Packet_ID( static_cast<unsigned char>(17) )
		, 		Packet_Size( static_cast<unsigned char>(24) )
		, 		View_ID( static_cast<unsigned short>(0) )
		, 		Sensor_ID( static_cast<unsigned char>(0) )
		, 		Gain( static_cast<float>(0.0f) )
		, 		Level( static_cast<float>(0.0f) )
		, 		AC_Coupling( static_cast<float>(0.0f) )
		, 		Noise( static_cast<float>(0.0f) )
	{
		set_Sensor_Enable( static_cast<GenericBoolState>(0) );
		set_Polarity( static_cast<SensorPolarityState>(0) );
		set_Line_by_Line_Dropout_Enable( static_cast<GenericBoolState>(0) );
		set_Automatic_Gain( static_cast<GenericBoolState>(0) );
		set_Track_White_Black( static_cast<SensorTrackState>(0) );
		set_Track_Mode( static_cast<SensorTrackModeState>(0) );
		set_Response_Type( static_cast<SensorResponseType>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_View_ID() const
	{
		return static_cast<unsigned short>(View_ID);
	}
	void set_View_ID( unsigned short value )
	{
		View_ID = static_cast<unsigned short>( value );
	}
	unsigned char get_Sensor_ID() const
	{
		return static_cast<unsigned char>(Sensor_ID);
	}
	void set_Sensor_ID( unsigned char value )
	{
		Sensor_ID = static_cast<unsigned char>( value );
	}
	GenericBoolState get_Sensor_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Sensor_Enable( GenericBoolState value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	SensorPolarityState get_Polarity() const
	{
		return static_cast<SensorPolarityState>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Polarity( SensorPolarityState value )
	{
		setBits<unsigned char,1,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Line_by_Line_Dropout_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Line_by_Line_Dropout_Enable( GenericBoolState value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Automatic_Gain() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 3, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Automatic_Gain( GenericBoolState value )
	{
		setBits<unsigned char,3,1>( BitsGroup_0, value );
	}
	SensorTrackState get_Track_White_Black() const
	{
		return static_cast<SensorTrackState>( extractBits<unsigned int, 4, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Track_White_Black( SensorTrackState value )
	{
		setBits<unsigned char,4,1>( BitsGroup_0, value );
	}
	SensorTrackModeState get_Track_Mode() const
	{
		return static_cast<SensorTrackModeState>( extractBits<unsigned int, 5, 3>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Track_Mode( SensorTrackModeState value )
	{
		setBits<unsigned char,5,3>( BitsGroup_0, value );
	}
	SensorResponseType get_Response_Type() const
	{
		return static_cast<SensorResponseType>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_1 ) );
	}
	void set_Response_Type( SensorResponseType value )
	{
		setBits<unsigned char,0,1>( BitsGroup_1, value );
	}
	float get_Gain() const
	{
		return static_cast<float>(Gain);
	}
	void set_Gain( float value )
	{
		Gain = static_cast<float>( value );
	}
	float get_Level() const
	{
		return static_cast<float>(Level);
	}
	void set_Level( float value )
	{
		Level = static_cast<float>( value );
	}
	float get_AC_Coupling() const
	{
		return static_cast<float>(AC_Coupling);
	}
	void set_AC_Coupling( float value )
	{
		AC_Coupling = static_cast<float>( value );
	}
	float get_Noise() const
	{
		return static_cast<float>(Noise);
	}
	void set_Noise( float value )
	{
		Noise = static_cast<float>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 17
	unsigned char Packet_ID;

	// Default value: 24
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short View_ID;

	// Default value: 0
	unsigned char Sensor_ID;

	// Bits are for:
		// Sensor Enable (1 bits) (Default: 0)
		// Polarity (1 bits) (Default: 0)
		// Line by Line Dropout Enable (1 bits) (Default: 0)
		// Automatic Gain (1 bits) (Default: 0)
		// Track White/Black (1 bits) (Default: 0)
		// Track Mode (3 bits) (Default: 0)
	unsigned char BitsGroup_0;

	// Bits are for:
		// Response Type (1 bits) (Default: 0)
		//  (7 bits) (Default: )
	unsigned char BitsGroup_1;

	char Reserved_0;

	// Default value: 0.0f
	float Gain;

	// Default value: 0.0f
	float Level;

	// Default value: 0.0f
	float AC_Coupling;

	// Default value: 0.0f
	float Noise;

};

//===------------------------------===//
// Trajectory Definition
// 
//===------------------------------===//
class Trajectory_Definition : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 24,
		PACKET_ID = 20
	};
	Trajectory_Definition() :
		Packet_ID( static_cast<unsigned char>(20) )
		, 		Packet_Size( static_cast<unsigned char>(24) )
		, 		Entity_ID( static_cast<unsigned short>(0) )
		, 		Acceleration_X( static_cast<float>(0.0f) )
		, 		Acceleration_Y( static_cast<float>(0.0f) )
		, 		Acceleration_Z( static_cast<float>(0.0f) )
		, 		Retardation_Rate( static_cast<float>(0.0f) )
		, 		Terminal_Velocity( static_cast<float>(0.0f) )
	{
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_Entity_ID() const
	{
		return static_cast<unsigned short>(Entity_ID);
	}
	void set_Entity_ID( unsigned short value )
	{
		Entity_ID = static_cast<unsigned short>( value );
	}
	float get_Acceleration_X() const
	{
		return static_cast<float>(Acceleration_X);
	}
	void set_Acceleration_X( float value )
	{
		Acceleration_X = static_cast<float>( value );
	}
	float get_Acceleration_Y() const
	{
		return static_cast<float>(Acceleration_Y);
	}
	void set_Acceleration_Y( float value )
	{
		Acceleration_Y = static_cast<float>( value );
	}
	float get_Acceleration_Z() const
	{
		return static_cast<float>(Acceleration_Z);
	}
	void set_Acceleration_Z( float value )
	{
		Acceleration_Z = static_cast<float>( value );
	}
	float get_Retardation_Rate() const
	{
		return static_cast<float>(Retardation_Rate);
	}
	void set_Retardation_Rate( float value )
	{
		Retardation_Rate = static_cast<float>( value );
	}
	float get_Terminal_Velocity() const
	{
		return static_cast<float>(Terminal_Velocity);
	}
	void set_Terminal_Velocity( float value )
	{
		Terminal_Velocity = static_cast<float>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 20
	unsigned char Packet_ID;

	// Default value: 24
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short Entity_ID;

	// Default value: 0.0f
	float Acceleration_X;

	// Default value: 0.0f
	float Acceleration_Y;

	// Default value: 0.0f
	float Acceleration_Z;

	// Default value: 0.0f
	float Retardation_Rate;

	// Default value: 0.0f
	float Terminal_Velocity;

};

//===------------------------------===//
// View Definition
// 
//===------------------------------===//
class View_Definition : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 32,
		PACKET_ID = 21
	};
	View_Definition() :
		Packet_ID( static_cast<unsigned char>(21) )
		, 		Packet_Size( static_cast<unsigned char>(32) )
		, 		View_ID( static_cast<unsigned short>(0) )
		, 		Group_ID( static_cast<unsigned char>(0) )
		, 		Near( static_cast<float>(0.0f) )
		, 		Far( static_cast<float>(0.0f) )
		, 		Left( static_cast<float>(0.0f) )
		, 		Right( static_cast<float>(0.0f) )
		, 		Top( static_cast<float>(0.0f) )
		, 		Bottom( static_cast<float>(0.0f) )
	{
		set_Near_Enable( static_cast<GenericBoolState>(0) );
		set_Far_Enable( static_cast<GenericBoolState>(0) );
		set_Left_Enable( static_cast<GenericBoolState>(0) );
		set_Right_Enable( static_cast<GenericBoolState>(0) );
		set_Top_Enable( static_cast<GenericBoolState>(0) );
		set_Bottom_Enable( static_cast<GenericBoolState>(0) );
		set_Mirror_Mode( static_cast<MirrorModeState>(0) );
		set_Pixel_Replication_Mode( static_cast<PixelReplicationState>(0) );
		set_Projection_Type( static_cast<ProjectionType>(0) );
		set_Reorder( static_cast<ReorderState>(0) );
		set_View_Type( static_cast<unsigned char>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_View_ID() const
	{
		return static_cast<unsigned short>(View_ID);
	}
	void set_View_ID( unsigned short value )
	{
		View_ID = static_cast<unsigned short>( value );
	}
	unsigned char get_Group_ID() const
	{
		return static_cast<unsigned char>(Group_ID);
	}
	void set_Group_ID( unsigned char value )
	{
		Group_ID = static_cast<unsigned char>( value );
	}
	GenericBoolState get_Near_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Near_Enable( GenericBoolState value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Far_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Far_Enable( GenericBoolState value )
	{
		setBits<unsigned char,1,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Left_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Left_Enable( GenericBoolState value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Right_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 3, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Right_Enable( GenericBoolState value )
	{
		setBits<unsigned char,3,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Top_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 4, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Top_Enable( GenericBoolState value )
	{
		setBits<unsigned char,4,1>( BitsGroup_0, value );
	}
	GenericBoolState get_Bottom_Enable() const
	{
		return static_cast<GenericBoolState>( extractBits<unsigned int, 5, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Bottom_Enable( GenericBoolState value )
	{
		setBits<unsigned char,5,1>( BitsGroup_0, value );
	}
	MirrorModeState get_Mirror_Mode() const
	{
		return static_cast<MirrorModeState>( extractBits<unsigned int, 6, 2>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Mirror_Mode( MirrorModeState value )
	{
		setBits<unsigned char,6,2>( BitsGroup_0, value );
	}
	PixelReplicationState get_Pixel_Replication_Mode() const
	{
		return static_cast<PixelReplicationState>( extractBits<unsigned int, 0, 3>( (unsigned int)BitsGroup_1 ) );
	}
	void set_Pixel_Replication_Mode( PixelReplicationState value )
	{
		setBits<unsigned char,0,3>( BitsGroup_1, value );
	}
	ProjectionType get_Projection_Type() const
	{
		return static_cast<ProjectionType>( extractBits<unsigned int, 3, 1>( (unsigned int)BitsGroup_1 ) );
	}
	void set_Projection_Type( ProjectionType value )
	{
		setBits<unsigned char,3,1>( BitsGroup_1, value );
	}
	ReorderState get_Reorder() const
	{
		return static_cast<ReorderState>( extractBits<unsigned int, 4, 1>( (unsigned int)BitsGroup_1 ) );
	}
	void set_Reorder( ReorderState value )
	{
		setBits<unsigned char,4,1>( BitsGroup_1, value );
	}
	unsigned char get_View_Type() const
	{
		return static_cast<unsigned char>( extractBits<unsigned int, 5, 3>( (unsigned int)BitsGroup_1 ) );
	}
	void set_View_Type( unsigned char value )
	{
		setBits<unsigned char,5,3>( BitsGroup_1, value );
	}
	float get_Near() const
	{
		return static_cast<float>(Near);
	}
	void set_Near( float value )
	{
		Near = static_cast<float>( value );
	}
	float get_Far() const
	{
		return static_cast<float>(Far);
	}
	void set_Far( float value )
	{
		Far = static_cast<float>( value );
	}
	float get_Left() const
	{
		return static_cast<float>(Left);
	}
	void set_Left( float value )
	{
		Left = static_cast<float>( value );
	}
	float get_Right() const
	{
		return static_cast<float>(Right);
	}
	void set_Right( float value )
	{
		Right = static_cast<float>( value );
	}
	float get_Top() const
	{
		return static_cast<float>(Top);
	}
	void set_Top( float value )
	{
		Top = static_cast<float>( value );
	}
	float get_Bottom() const
	{
		return static_cast<float>(Bottom);
	}
	void set_Bottom( float value )
	{
		Bottom = static_cast<float>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 21
	unsigned char Packet_ID;

	// Default value: 32
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short View_ID;

	// Default value: 0
	unsigned char Group_ID;

	// Bits are for:
		// Near Enable (1 bits) (Default: 0)
		// Far Enable (1 bits) (Default: 0)
		// Left Enable (1 bits) (Default: 0)
		// Right Enable (1 bits) (Default: 0)
		// Top Enable (1 bits) (Default: 0)
		// Bottom Enable (1 bits) (Default: 0)
		// Mirror Mode (2 bits) (Default: 0)
	unsigned char BitsGroup_0;

	// Bits are for:
		// Pixel Replication Mode (3 bits) (Default: 0)
		// Projection Type (1 bits) (Default: 0)
		// Reorder (1 bits) (Default: 0)
		// View Type (3 bits) (Default: 0)
	unsigned char BitsGroup_1;

	char Reserved_0;

	// Default value: 0.0f
	float Near;

	// Default value: 0.0f
	float Far;

	// Default value: 0.0f
	float Left;

	// Default value: 0.0f
	float Right;

	// Default value: 0.0f
	float Top;

	// Default value: 0.0f
	float Bottom;

};

//===------------------------------===//
// HAT/HOT Request
// 
//===------------------------------===//
class HAT_HOT_Request : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 32,
		PACKET_ID = 24
	};
	HAT_HOT_Request() :
		Packet_ID( static_cast<unsigned char>(24) )
		, 		Packet_Size( static_cast<unsigned char>(32) )
		, 		HAT_HOT_ID( static_cast<unsigned short>(0) )
		, 		Update_Period( static_cast<unsigned char>(0) )
		, 		Entity_ID( static_cast<unsigned short>(0) )
		, 		Latitude_X_Offset( static_cast<double>(0.0) )
		, 		Longitude_Y_Offset( static_cast<double>(0.0) )
		, 		Altitude_Z_Offset( static_cast<double>(0.0) )
	{
		set_Request_Type( static_cast<HATHOTRequestType>(0) );
		set_Coordinate_System( static_cast<GeodeticEntityCS>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_HAT_HOT_ID() const
	{
		return static_cast<unsigned short>(HAT_HOT_ID);
	}
	void set_HAT_HOT_ID( unsigned short value )
	{
		HAT_HOT_ID = static_cast<unsigned short>( value );
	}
	HATHOTRequestType get_Request_Type() const
	{
		return static_cast<HATHOTRequestType>( extractBits<unsigned int, 0, 2>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Request_Type( HATHOTRequestType value )
	{
		setBits<unsigned char,0,2>( BitsGroup_0, value );
	}
	GeodeticEntityCS get_Coordinate_System() const
	{
		return static_cast<GeodeticEntityCS>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Coordinate_System( GeodeticEntityCS value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	unsigned char get_Update_Period() const
	{
		return static_cast<unsigned char>(Update_Period);
	}
	void set_Update_Period( unsigned char value )
	{
		Update_Period = static_cast<unsigned char>( value );
	}
	unsigned short get_Entity_ID() const
	{
		return static_cast<unsigned short>(Entity_ID);
	}
	void set_Entity_ID( unsigned short value )
	{
		Entity_ID = static_cast<unsigned short>( value );
	}
	double get_Latitude_X_Offset() const
	{
		return static_cast<double>(Latitude_X_Offset);
	}
	void set_Latitude_X_Offset( double value )
	{
		Latitude_X_Offset = static_cast<double>( value );
	}
	double get_Longitude_Y_Offset() const
	{
		return static_cast<double>(Longitude_Y_Offset);
	}
	void set_Longitude_Y_Offset( double value )
	{
		Longitude_Y_Offset = static_cast<double>( value );
	}
	double get_Altitude_Z_Offset() const
	{
		return static_cast<double>(Altitude_Z_Offset);
	}
	void set_Altitude_Z_Offset( double value )
	{
		Altitude_Z_Offset = static_cast<double>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 24
	unsigned char Packet_ID;

	// Default value: 32
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short HAT_HOT_ID;

	char Reserved_0;

	// Bits are for:
		// Request Type (2 bits) (Default: 0)
		// Coordinate System (1 bits) (Default: 0)
		//  (5 bits) (Default: )
	unsigned char BitsGroup_0;

	// Default value: 0
	unsigned char Update_Period;

	// Default value: 0
	unsigned short Entity_ID;

	// Default value: 0.0
	double Latitude_X_Offset;

	// Default value: 0.0
	double Longitude_Y_Offset;

	// Default value: 0.0
	double Altitude_Z_Offset;

};

//===------------------------------===//
// LOS Segment Request
// 
//===------------------------------===//
class LOS_Segment_Request : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 64,
		PACKET_ID = 25
	};
	LOS_Segment_Request() :
		Packet_ID( static_cast<unsigned char>(25) )
		, 		Packet_Size( static_cast<unsigned char>(64) )
		, 		LOS_ID( static_cast<unsigned short>(0) )
		, 		Alpha_Threshold( static_cast<unsigned char>(0) )
		, 		Source_Entity_ID( static_cast<unsigned short>(0) )
		, 		Source_Latitude_X_Offset( static_cast<double>(0.0) )
		, 		Source_Longitude_Y_Offset( static_cast<double>(0.0) )
		, 		Source_Altitude_Z_Offset( static_cast<double>(0.0) )
		, 		Destination_Latitude_X_Offset( static_cast<double>(0.0) )
		, 		Destination_Longitude_Y_Offset( static_cast<double>(0.0) )
		, 		Destination_Altitude_Z_Offset( static_cast<double>(0.0) )
		, 		Material_Mask( static_cast<unsigned int>(0) )
		, 		Update_Period( static_cast<unsigned char>(0) )
		, 		Destination_Entity_ID( static_cast<unsigned short>(0) )
	{
		set_Request_Type( static_cast<LOSRequestType>(0) );
		set_Source_Point_CS( static_cast<GeodeticEntityCS>(0) );
		set_Destination_Point_CS( static_cast<GeodeticEntityCS>(0) );
		set_Response_CS( static_cast<GeodeticEntityCS>(0) );
		set_Destination_Entity_ID_Valid( static_cast<GenericValidState>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_LOS_ID() const
	{
		return static_cast<unsigned short>(LOS_ID);
	}
	void set_LOS_ID( unsigned short value )
	{
		LOS_ID = static_cast<unsigned short>( value );
	}
	LOSRequestType get_Request_Type() const
	{
		return static_cast<LOSRequestType>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Request_Type( LOSRequestType value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	GeodeticEntityCS get_Source_Point_CS() const
	{
		return static_cast<GeodeticEntityCS>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Source_Point_CS( GeodeticEntityCS value )
	{
		setBits<unsigned char,1,1>( BitsGroup_0, value );
	}
	GeodeticEntityCS get_Destination_Point_CS() const
	{
		return static_cast<GeodeticEntityCS>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Destination_Point_CS( GeodeticEntityCS value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	GeodeticEntityCS get_Response_CS() const
	{
		return static_cast<GeodeticEntityCS>( extractBits<unsigned int, 3, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Response_CS( GeodeticEntityCS value )
	{
		setBits<unsigned char,3,1>( BitsGroup_0, value );
	}
	GenericValidState get_Destination_Entity_ID_Valid() const
	{
		return static_cast<GenericValidState>( extractBits<unsigned int, 4, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Destination_Entity_ID_Valid( GenericValidState value )
	{
		setBits<unsigned char,4,1>( BitsGroup_0, value );
	}
	unsigned char get_Alpha_Threshold() const
	{
		return static_cast<unsigned char>(Alpha_Threshold);
	}
	void set_Alpha_Threshold( unsigned char value )
	{
		Alpha_Threshold = static_cast<unsigned char>( value );
	}
	unsigned short get_Source_Entity_ID() const
	{
		return static_cast<unsigned short>(Source_Entity_ID);
	}
	void set_Source_Entity_ID( unsigned short value )
	{
		Source_Entity_ID = static_cast<unsigned short>( value );
	}
	double get_Source_Latitude_X_Offset() const
	{
		return static_cast<double>(Source_Latitude_X_Offset);
	}
	void set_Source_Latitude_X_Offset( double value )
	{
		Source_Latitude_X_Offset = static_cast<double>( value );
	}
	double get_Source_Longitude_Y_Offset() const
	{
		return static_cast<double>(Source_Longitude_Y_Offset);
	}
	void set_Source_Longitude_Y_Offset( double value )
	{
		Source_Longitude_Y_Offset = static_cast<double>( value );
	}
	double get_Source_Altitude_Z_Offset() const
	{
		return static_cast<double>(Source_Altitude_Z_Offset);
	}
	void set_Source_Altitude_Z_Offset( double value )
	{
		Source_Altitude_Z_Offset = static_cast<double>( value );
	}
	double get_Destination_Latitude_X_Offset() const
	{
		return static_cast<double>(Destination_Latitude_X_Offset);
	}
	void set_Destination_Latitude_X_Offset( double value )
	{
		Destination_Latitude_X_Offset = static_cast<double>( value );
	}
	double get_Destination_Longitude_Y_Offset() const
	{
		return static_cast<double>(Destination_Longitude_Y_Offset);
	}
	void set_Destination_Longitude_Y_Offset( double value )
	{
		Destination_Longitude_Y_Offset = static_cast<double>( value );
	}
	double get_Destination_Altitude_Z_Offset() const
	{
		return static_cast<double>(Destination_Altitude_Z_Offset);
	}
	void set_Destination_Altitude_Z_Offset( double value )
	{
		Destination_Altitude_Z_Offset = static_cast<double>( value );
	}
	unsigned int get_Material_Mask() const
	{
		return static_cast<unsigned int>(Material_Mask);
	}
	void set_Material_Mask( unsigned int value )
	{
		Material_Mask = static_cast<unsigned int>( value );
	}
	unsigned char get_Update_Period() const
	{
		return static_cast<unsigned char>(Update_Period);
	}
	void set_Update_Period( unsigned char value )
	{
		Update_Period = static_cast<unsigned char>( value );
	}
	unsigned short get_Destination_Entity_ID() const
	{
		return static_cast<unsigned short>(Destination_Entity_ID);
	}
	void set_Destination_Entity_ID( unsigned short value )
	{
		Destination_Entity_ID = static_cast<unsigned short>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 25
	unsigned char Packet_ID;

	// Default value: 64
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short LOS_ID;

	// Bits are for:
		// Request Type (1 bits) (Default: 0)
		// Source Point CS (1 bits) (Default: 0)
		// Destination Point CS (1 bits) (Default: 0)
		// Response CS (1 bits) (Default: 0)
		// Destination Entity ID Valid (1 bits) (Default: 0)
		//  (3 bits) (Default: )
	unsigned char BitsGroup_0;

	// Default value: 0
	unsigned char Alpha_Threshold;

	// Default value: 0
	unsigned short Source_Entity_ID;

	// Default value: 0.0
	double Source_Latitude_X_Offset;

	// Default value: 0.0
	double Source_Longitude_Y_Offset;

	// Default value: 0.0
	double Source_Altitude_Z_Offset;

	// Default value: 0.0
	double Destination_Latitude_X_Offset;

	// Default value: 0.0
	double Destination_Longitude_Y_Offset;

	// Default value: 0.0
	double Destination_Altitude_Z_Offset;

	// Default value: 0
	unsigned int Material_Mask;

	// Default value: 0
	unsigned char Update_Period;

	char Reserved_0;

	// Default value: 0
	unsigned short Destination_Entity_ID;

};

//===------------------------------===//
// LOS Vector Request
// 
//===------------------------------===//
class LOS_Vector_Request : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 56,
		PACKET_ID = 26
	};
	LOS_Vector_Request() :
		Packet_ID( static_cast<unsigned char>(26) )
		, 		Packet_Size( static_cast<unsigned char>(56) )
		, 		LOS_ID( static_cast<unsigned short>(0) )
		, 		Alpha_Threshold( static_cast<unsigned char>(0) )
		, 		Entity_ID( static_cast<unsigned short>(0) )
		, 		Azimuth( static_cast<float>(0.0f) )
		, 		Elevation( static_cast<float>(0.0f) )
		, 		Minimum_Range( static_cast<float>(0.0f) )
		, 		Maximum_Range( static_cast<float>(0.0f) )
		, 		Source_Latitude_X_Offset( static_cast<double>(0.0) )
		, 		Source_Longitude_Y_Offset( static_cast<double>(0.0) )
		, 		Source_Altitude_Z_Offset( static_cast<double>(0.0) )
		, 		Material_Mask( static_cast<unsigned int>(0) )
		, 		Update_Period( static_cast<unsigned char>(0) )
	{
		set_Request_Type( static_cast<LOSRequestType>(0) );
		set_Source_Point_CS( static_cast<GeodeticEntityCS>(0) );
		set_Response_CS( static_cast<GeodeticEntityCS>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_LOS_ID() const
	{
		return static_cast<unsigned short>(LOS_ID);
	}
	void set_LOS_ID( unsigned short value )
	{
		LOS_ID = static_cast<unsigned short>( value );
	}
	LOSRequestType get_Request_Type() const
	{
		return static_cast<LOSRequestType>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Request_Type( LOSRequestType value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	GeodeticEntityCS get_Source_Point_CS() const
	{
		return static_cast<GeodeticEntityCS>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Source_Point_CS( GeodeticEntityCS value )
	{
		setBits<unsigned char,1,1>( BitsGroup_0, value );
	}
	GeodeticEntityCS get_Response_CS() const
	{
		return static_cast<GeodeticEntityCS>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Response_CS( GeodeticEntityCS value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	unsigned char get_Alpha_Threshold() const
	{
		return static_cast<unsigned char>(Alpha_Threshold);
	}
	void set_Alpha_Threshold( unsigned char value )
	{
		Alpha_Threshold = static_cast<unsigned char>( value );
	}
	unsigned short get_Entity_ID() const
	{
		return static_cast<unsigned short>(Entity_ID);
	}
	void set_Entity_ID( unsigned short value )
	{
		Entity_ID = static_cast<unsigned short>( value );
	}
	float get_Azimuth() const
	{
		return static_cast<float>(Azimuth);
	}
	void set_Azimuth( float value )
	{
		Azimuth = static_cast<float>( value );
	}
	float get_Elevation() const
	{
		return static_cast<float>(Elevation);
	}
	void set_Elevation( float value )
	{
		Elevation = static_cast<float>( value );
	}
	float get_Minimum_Range() const
	{
		return static_cast<float>(Minimum_Range);
	}
	void set_Minimum_Range( float value )
	{
		Minimum_Range = static_cast<float>( value );
	}
	float get_Maximum_Range() const
	{
		return static_cast<float>(Maximum_Range);
	}
	void set_Maximum_Range( float value )
	{
		Maximum_Range = static_cast<float>( value );
	}
	double get_Source_Latitude_X_Offset() const
	{
		return static_cast<double>(Source_Latitude_X_Offset);
	}
	void set_Source_Latitude_X_Offset( double value )
	{
		Source_Latitude_X_Offset = static_cast<double>( value );
	}
	double get_Source_Longitude_Y_Offset() const
	{
		return static_cast<double>(Source_Longitude_Y_Offset);
	}
	void set_Source_Longitude_Y_Offset( double value )
	{
		Source_Longitude_Y_Offset = static_cast<double>( value );
	}
	double get_Source_Altitude_Z_Offset() const
	{
		return static_cast<double>(Source_Altitude_Z_Offset);
	}
	void set_Source_Altitude_Z_Offset( double value )
	{
		Source_Altitude_Z_Offset = static_cast<double>( value );
	}
	unsigned int get_Material_Mask() const
	{
		return static_cast<unsigned int>(Material_Mask);
	}
	void set_Material_Mask( unsigned int value )
	{
		Material_Mask = static_cast<unsigned int>( value );
	}
	unsigned char get_Update_Period() const
	{
		return static_cast<unsigned char>(Update_Period);
	}
	void set_Update_Period( unsigned char value )
	{
		Update_Period = static_cast<unsigned char>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 26
	unsigned char Packet_ID;

	// Default value: 56
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short LOS_ID;

	// Bits are for:
		// Request Type (1 bits) (Default: 0)
		// Source Point CS (1 bits) (Default: 0)
		// Response CS (1 bits) (Default: 0)
		//  (5 bits) (Default: )
	unsigned char BitsGroup_0;

	// Default value: 0
	unsigned char Alpha_Threshold;

	// Default value: 0
	unsigned short Entity_ID;

	// Default value: 0.0f
	float Azimuth;

	// Default value: 0.0f
	float Elevation;

	// Default value: 0.0f
	float Minimum_Range;

	// Default value: 0.0f
	float Maximum_Range;

	// Default value: 0.0
	double Source_Latitude_X_Offset;

	// Default value: 0.0
	double Source_Longitude_Y_Offset;

	// Default value: 0.0
	double Source_Altitude_Z_Offset;

	// Default value: 0
	unsigned int Material_Mask;

	// Default value: 0
	unsigned char Update_Period;

	char Reserved_0;

	short Reserved_1;

};

//===------------------------------===//
// Start Of Frame
// 
//===------------------------------===//
class Start_Of_Frame : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 24,
		PACKET_ID = 101
	};
	Start_Of_Frame() :
		Packet_ID( static_cast<unsigned char>(101) )
		, 		Packet_Size( static_cast<unsigned char>(24) )
		, 		Major_Version( static_cast<unsigned char>(3) )
		, 		Database_Number( static_cast<char>(0) )
		, 		IG_Status_Code( static_cast<unsigned char>(0) )
		, 		Byte_Swap_Magic_Number( static_cast<unsigned short>(32768) )
		, 		IG_Frame_Number( static_cast<unsigned int>(0) )
		, 		Timestamp( static_cast<unsigned int>(0) )
		, 		Last_Host_Frame_Number( static_cast<unsigned int>(0) )
	{
		set_IG_Mode( static_cast<IGModeState>(0) );
		set_Timestamp_Valid( static_cast<GenericValidState>(0) );
		set_Earth_Reference_Model( static_cast<EarthRefModelType>(0) );
		set_Minor_Version( static_cast<unsigned char>(2) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned char get_Major_Version() const
	{
		return static_cast<unsigned char>(Major_Version);
	}
	char get_Database_Number() const
	{
		return static_cast<char>(Database_Number);
	}
	void set_Database_Number( char value )
	{
		Database_Number = static_cast<char>( value );
	}
	// (0) Normal operation (1-255) Defined by IG
	unsigned char get_IG_Status_Code() const
	{
		return static_cast<unsigned char>(IG_Status_Code);
	}
	void set_IG_Status_Code( unsigned char value )
	{
		IG_Status_Code = static_cast<unsigned char>( value );
	}
	IGModeState get_IG_Mode() const
	{
		return static_cast<IGModeState>( extractBits<unsigned int, 0, 2>( (unsigned int)BitsGroup_0 ) );
	}
	void set_IG_Mode( IGModeState value )
	{
		setBits<unsigned char,0,2>( BitsGroup_0, value );
	}
	GenericValidState get_Timestamp_Valid() const
	{
		return static_cast<GenericValidState>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Timestamp_Valid( GenericValidState value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	EarthRefModelType get_Earth_Reference_Model() const
	{
		return static_cast<EarthRefModelType>( extractBits<unsigned int, 3, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Earth_Reference_Model( EarthRefModelType value )
	{
		setBits<unsigned char,3,1>( BitsGroup_0, value );
	}
	unsigned char get_Minor_Version() const
	{
		return static_cast<unsigned char>( extractBits<unsigned int, 4, 4>( (unsigned int)BitsGroup_0 ) );
	}
	unsigned short get_Byte_Swap_Magic_Number() const
	{
		return static_cast<unsigned short>(Byte_Swap_Magic_Number);
	}
	unsigned int get_IG_Frame_Number() const
	{
		return static_cast<unsigned int>(IG_Frame_Number);
	}
	void set_IG_Frame_Number( unsigned int value )
	{
		IG_Frame_Number = static_cast<unsigned int>( value );
	}
	unsigned int get_Timestamp() const
	{
		return static_cast<unsigned int>(Timestamp);
	}
	void set_Timestamp( unsigned int value )
	{
		Timestamp = static_cast<unsigned int>( value );
	}
	unsigned int get_Last_Host_Frame_Number() const
	{
		return static_cast<unsigned int>(Last_Host_Frame_Number);
	}
	void set_Last_Host_Frame_Number( unsigned int value )
	{
		Last_Host_Frame_Number = static_cast<unsigned int>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
	void set_Major_Version( unsigned char value )
	{
		Major_Version = static_cast<unsigned char>( value );
	}
	void set_Minor_Version( unsigned char value )
	{
		setBits<unsigned char,4,4>( BitsGroup_0, value );
	}
	void set_Byte_Swap_Magic_Number( unsigned short value )
	{
		Byte_Swap_Magic_Number = static_cast<unsigned short>( value );
	}
protected:
	// Default value: 101
	unsigned char Packet_ID;

	// Default value: 24
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 3
	unsigned char Major_Version;

	// Default value: 0
	char Database_Number;

	// (0) Normal operation (1-255) Defined by IG
	// Default value: 0
	unsigned char IG_Status_Code;

	// Bits are for:
		// IG Mode (2 bits) (Default: 0)
		// Timestamp Valid (1 bits) (Default: 0)
		// Earth Reference Model (1 bits) (Default: 0)
		// Minor Version (4 bits) (Default: 2)
	unsigned char BitsGroup_0;

	// Default value: 32768
	unsigned short Byte_Swap_Magic_Number;

	// Default value: 0
	unsigned int IG_Frame_Number;

	// Default value: 0
	unsigned int Timestamp;

	// Default value: 0
	unsigned int Last_Host_Frame_Number;

	int Reserved_0;

};

//===------------------------------===//
// HAT/HOT Response
// 
//===------------------------------===//
class HAT_HOT_Response : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 16,
		PACKET_ID = 102
	};
	HAT_HOT_Response() :
		Packet_ID( static_cast<unsigned char>(102) )
		, 		Packet_Size( static_cast<unsigned char>(16) )
		, 		HAT_HOT_ID( static_cast<unsigned short>(0) )
		, 		Height( static_cast<double>(0.0) )
	{
		set_Valid( static_cast<GenericValidState>(0) );
		set_Response_Type( static_cast<HATHOTResponseType>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_HAT_HOT_ID() const
	{
		return static_cast<unsigned short>(HAT_HOT_ID);
	}
	void set_HAT_HOT_ID( unsigned short value )
	{
		HAT_HOT_ID = static_cast<unsigned short>( value );
	}
	GenericValidState get_Valid() const
	{
		return static_cast<GenericValidState>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Valid( GenericValidState value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	HATHOTResponseType get_Response_Type() const
	{
		return static_cast<HATHOTResponseType>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Response_Type( HATHOTResponseType value )
	{
		setBits<unsigned char,1,1>( BitsGroup_0, value );
	}
	unsigned char get_Host_Frame_Number_LSN() const
	{
		return static_cast<unsigned char>( extractBits<unsigned int, 4, 4>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Host_Frame_Number_LSN( unsigned char value )
	{
		setBits<unsigned char,4,4>( BitsGroup_0, value );
	}
	double get_Height() const
	{
		return static_cast<double>(Height);
	}
	void set_Height( double value )
	{
		Height = static_cast<double>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 102
	unsigned char Packet_ID;

	// Default value: 16
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short HAT_HOT_ID;

	// Bits are for:
		// Valid (1 bits) (Default: 0)
		// Response Type (1 bits) (Default: 0)
		//  (2 bits) (Default: )
		// Host Frame Number LSN (4 bits) (Default: )
	unsigned char BitsGroup_0;

	char Reserved_0;

	short Reserved_1;

	// Default value: 0.0
	double Height;

};

//===------------------------------===//
// HAT/HOT Extended Response
// 
//===------------------------------===//
class HAT_HOT_Extended_Response : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 40,
		PACKET_ID = 103
	};
	HAT_HOT_Extended_Response() :
		Packet_ID( static_cast<unsigned char>(103) )
		, 		Packet_Size( static_cast<unsigned char>(40) )
		, 		HAT_HOT_ID( static_cast<unsigned short>(0) )
		, 		HAT( static_cast<double>(0.0) )
		, 		HOT( static_cast<double>(0.0) )
		, 		Material_Code( static_cast<unsigned int>(0) )
		, 		Normal_Vector_Azimuth( static_cast<float>(0.0f) )
		, 		Normal_Vector_Elevation( static_cast<float>(0.0f) )
	{
		set_Valid( static_cast<GenericValidState>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_HAT_HOT_ID() const
	{
		return static_cast<unsigned short>(HAT_HOT_ID);
	}
	void set_HAT_HOT_ID( unsigned short value )
	{
		HAT_HOT_ID = static_cast<unsigned short>( value );
	}
	GenericValidState get_Valid() const
	{
		return static_cast<GenericValidState>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Valid( GenericValidState value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	unsigned char get_Host_Frame_Number_LSN() const
	{
		return static_cast<unsigned char>( extractBits<unsigned int, 4, 4>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Host_Frame_Number_LSN( unsigned char value )
	{
		setBits<unsigned char,4,4>( BitsGroup_0, value );
	}
	double get_HAT() const
	{
		return static_cast<double>(HAT);
	}
	void set_HAT( double value )
	{
		HAT = static_cast<double>( value );
	}
	double get_HOT() const
	{
		return static_cast<double>(HOT);
	}
	void set_HOT( double value )
	{
		HOT = static_cast<double>( value );
	}
	unsigned int get_Material_Code() const
	{
		return static_cast<unsigned int>(Material_Code);
	}
	void set_Material_Code( unsigned int value )
	{
		Material_Code = static_cast<unsigned int>( value );
	}
	float get_Normal_Vector_Azimuth() const
	{
		return static_cast<float>(Normal_Vector_Azimuth);
	}
	void set_Normal_Vector_Azimuth( float value )
	{
		Normal_Vector_Azimuth = static_cast<float>( value );
	}
	float get_Normal_Vector_Elevation() const
	{
		return static_cast<float>(Normal_Vector_Elevation);
	}
	void set_Normal_Vector_Elevation( float value )
	{
		Normal_Vector_Elevation = static_cast<float>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 103
	unsigned char Packet_ID;

	// Default value: 40
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short HAT_HOT_ID;

	// Bits are for:
		// Valid (1 bits) (Default: 0)
		//  (3 bits) (Default: )
		// Host Frame Number LSN (4 bits) (Default: )
	unsigned char BitsGroup_0;

	char Reserved_0;

	short Reserved_1;

	// Default value: 0.0
	double HAT;

	// Default value: 0.0
	double HOT;

	// Default value: 0
	unsigned int Material_Code;

	// Default value: 0.0f
	float Normal_Vector_Azimuth;

	// Default value: 0.0f
	float Normal_Vector_Elevation;

	int Reserved_2;

};

//===------------------------------===//
// LOS Response
// 
//===------------------------------===//
class LOS_Response : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 16,
		PACKET_ID = 104
	};
	LOS_Response() :
		Packet_ID( static_cast<unsigned char>(104) )
		, 		Packet_Size( static_cast<unsigned char>(16) )
		, 		LOS_ID( static_cast<unsigned short>(0) )
		, 		Response_Count( static_cast<unsigned char>(0) )
		, 		Entity_ID( static_cast<unsigned short>(0) )
		, 		Range( static_cast<double>(0.0) )
	{
		set_Valid( static_cast<GenericValidState>(0) );
		set_Entity_ID_Valid( static_cast<GenericValidState>(0) );
		set_Visible( static_cast<VisibleState>(0) );
		set_Host_Frame_Number_LSN( static_cast<unsigned char>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_LOS_ID() const
	{
		return static_cast<unsigned short>(LOS_ID);
	}
	void set_LOS_ID( unsigned short value )
	{
		LOS_ID = static_cast<unsigned short>( value );
	}
	GenericValidState get_Valid() const
	{
		return static_cast<GenericValidState>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Valid( GenericValidState value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	GenericValidState get_Entity_ID_Valid() const
	{
		return static_cast<GenericValidState>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Entity_ID_Valid( GenericValidState value )
	{
		setBits<unsigned char,1,1>( BitsGroup_0, value );
	}
	VisibleState get_Visible() const
	{
		return static_cast<VisibleState>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Visible( VisibleState value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	unsigned char get_Host_Frame_Number_LSN() const
	{
		return static_cast<unsigned char>( extractBits<unsigned int, 4, 4>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Host_Frame_Number_LSN( unsigned char value )
	{
		setBits<unsigned char,4,4>( BitsGroup_0, value );
	}
	unsigned char get_Response_Count() const
	{
		return static_cast<unsigned char>(Response_Count);
	}
	void set_Response_Count( unsigned char value )
	{
		Response_Count = static_cast<unsigned char>( value );
	}
	unsigned short get_Entity_ID() const
	{
		return static_cast<unsigned short>(Entity_ID);
	}
	void set_Entity_ID( unsigned short value )
	{
		Entity_ID = static_cast<unsigned short>( value );
	}
	double get_Range() const
	{
		return static_cast<double>(Range);
	}
	void set_Range( double value )
	{
		Range = static_cast<double>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 104
	unsigned char Packet_ID;

	// Default value: 16
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short LOS_ID;

	// Bits are for:
		// Valid (1 bits) (Default: 0)
		// Entity ID Valid (1 bits) (Default: 0)
		// Visible (1 bits) (Default: 0)
		//  (1 bits) (Default: )
		// Host Frame Number LSN (4 bits) (Default: 0)
	unsigned char BitsGroup_0;

	// Default value: 0
	unsigned char Response_Count;

	// Default value: 0
	unsigned short Entity_ID;

	// Default value: 0.0
	double Range;

};

//===------------------------------===//
// LOS Extended Response
// 
//===------------------------------===//
class LOS_Extended_Response : public BasePacket
{
public:
	enum
	{
		PACKET_SIZE = 56,
		PACKET_ID = 105
	};
	LOS_Extended_Response() :
		Packet_ID( static_cast<unsigned char>(105) )
		, 		Packet_Size( static_cast<unsigned char>(56) )
		, 		LOS_ID( static_cast<unsigned short>(0) )
		, 		Response_Count( static_cast<unsigned char>(0) )
		, 		Entity_ID( static_cast<unsigned short>(0) )
		, 		Range( static_cast<double>(0.0) )
		, 		Latitude_X_Offset( static_cast<double>(0.0) )
		, 		Longitude_Y_Offset( static_cast<double>(0.0) )
		, 		Altitude_Z_Offset( static_cast<double>(0.0) )
		, 		Red( static_cast<unsigned char>(0) )
		, 		Green( static_cast<unsigned char>(0) )
		, 		Blue( static_cast<unsigned char>(0) )
		, 		Alpha( static_cast<unsigned char>(255) )
		, 		Material_Code( static_cast<unsigned int>(0) )
		, 		Normal_Vector_Azimuth( static_cast<float>(0.0f) )
		, 		Normal_Vector_Elevation( static_cast<float>(0.0f) )
	{
		set_Valid( static_cast<GenericValidState>(0) );
		set_Entity_ID_Valid( static_cast<GenericValidState>(0) );
		set_Range_Valid( static_cast<GenericValidState>(0) );
		set_Visible( static_cast<VisibleState>(0) );
	}

	virtual unsigned int getType(){ return (unsigned int)PACKET_ID; }

	virtual size_t loadFromBinaryStream(const unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(&Packet_ID, data, PACKET_SIZE);
		return PACKET_SIZE;
	}

	virtual size_t saveToBinaryStream(unsigned char* data, size_t s)
	{
		if (s < PACKET_SIZE) return 0;
		memcpy(data, &Packet_ID, PACKET_SIZE);
		return PACKET_SIZE;
	}

public:
	unsigned char get_Packet_ID() const
	{
		return static_cast<unsigned char>(Packet_ID);
	}
	unsigned char get_Packet_Size() const
	{
		return static_cast<unsigned char>(Packet_Size);
	}
	unsigned short get_LOS_ID() const
	{
		return static_cast<unsigned short>(LOS_ID);
	}
	void set_LOS_ID( unsigned short value )
	{
		LOS_ID = static_cast<unsigned short>( value );
	}
	GenericValidState get_Valid() const
	{
		return static_cast<GenericValidState>( extractBits<unsigned int, 0, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Valid( GenericValidState value )
	{
		setBits<unsigned char,0,1>( BitsGroup_0, value );
	}
	GenericValidState get_Entity_ID_Valid() const
	{
		return static_cast<GenericValidState>( extractBits<unsigned int, 1, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Entity_ID_Valid( GenericValidState value )
	{
		setBits<unsigned char,1,1>( BitsGroup_0, value );
	}
	GenericValidState get_Range_Valid() const
	{
		return static_cast<GenericValidState>( extractBits<unsigned int, 2, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Range_Valid( GenericValidState value )
	{
		setBits<unsigned char,2,1>( BitsGroup_0, value );
	}
	VisibleState get_Visible() const
	{
		return static_cast<VisibleState>( extractBits<unsigned int, 3, 1>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Visible( VisibleState value )
	{
		setBits<unsigned char,3,1>( BitsGroup_0, value );
	}
	unsigned char get_Host_Frame_Number_LSN() const
	{
		return static_cast<unsigned char>( extractBits<unsigned int, 4, 4>( (unsigned int)BitsGroup_0 ) );
	}
	void set_Host_Frame_Number_LSN( unsigned char value )
	{
		setBits<unsigned char,4,4>( BitsGroup_0, value );
	}
	unsigned char get_Response_Count() const
	{
		return static_cast<unsigned char>(Response_Count);
	}
	void set_Response_Count( unsigned char value )
	{
		Response_Count = static_cast<unsigned char>( value );
	}
	unsigned short get_Entity_ID() const
	{
		return static_cast<unsigned short>(Entity_ID);
	}
	void set_Entity_ID( unsigned short value )
	{
		Entity_ID = static_cast<unsigned short>( value );
	}
	double get_Range() const
	{
		return static_cast<double>(Range);
	}
	void set_Range( double value )
	{
		Range = static_cast<double>( value );
	}
	double get_Latitude_X_Offset() const
	{
		return static_cast<double>(Latitude_X_Offset);
	}
	void set_Latitude_X_Offset( double value )
	{
		Latitude_X_Offset = static_cast<double>( value );
	}
	double get_Longitude_Y_Offset() const
	{
		return static_cast<double>(Longitude_Y_Offset);
	}
	void set_Longitude_Y_Offset( double value )
	{
		Longitude_Y_Offset = static_cast<double>( value );
	}
	double get_Altitude_Z_Offset() const
	{
		return static_cast<double>(Altitude_Z_Offset);
	}
	void set_Altitude_Z_Offset( double value )
	{
		Altitude_Z_Offset = static_cast<double>( value );
	}
	unsigned char get_Red() const
	{
		return static_cast<unsigned char>(Red);
	}
	void set_Red( unsigned char value )
	{
		Red = static_cast<unsigned char>( value );
	}
	unsigned char get_Green() const
	{
		return static_cast<unsigned char>(Green);
	}
	void set_Green( unsigned char value )
	{
		Green = static_cast<unsigned char>( value );
	}
	unsigned char get_Blue() const
	{
		return static_cast<unsigned char>(Blue);
	}
	void set_Blue( unsigned char value )
	{
		Blue = static_cast<unsigned char>( value );
	}
	unsigned char get_Alpha() const
	{
		return static_cast<unsigned char>(Alpha);
	}
	void set_Alpha( unsigned char value )
	{
		Alpha = static_cast<unsigned char>( value );
	}
	unsigned int get_Material_Code() const
	{
		return static_cast<unsigned int>(Material_Code);
	}
	void set_Material_Code( unsigned int value )
	{
		Material_Code = static_cast<unsigned int>( value );
	}
	float get_Normal_Vector_Azimuth() const
	{
		return static_cast<float>(Normal_Vector_Azimuth);
	}
	void set_Normal_Vector_Azimuth( float value )
	{
		Normal_Vector_Azimuth = static_cast<float>( value );
	}
	float get_Normal_Vector_Elevation() const
	{
		return static_cast<float>(Normal_Vector_Elevation);
	}
	void set_Normal_Vector_Elevation( float value )
	{
		Normal_Vector_Elevation = static_cast<float>( value );
	}

protected:
	void set_Packet_ID( unsigned char value )
	{
		Packet_ID = static_cast<unsigned char>( value );
	}
	void set_Packet_Size( unsigned char value )
	{
		Packet_Size = static_cast<unsigned char>( value );
	}
protected:
	// Default value: 105
	unsigned char Packet_ID;

	// Default value: 56
	// Units: bytes
	unsigned char Packet_Size;

	// Default value: 0
	unsigned short LOS_ID;

	// Bits are for:
		// Valid (1 bits) (Default: 0)
		// Entity ID Valid (1 bits) (Default: 0)
		// Range Valid (1 bits) (Default: 0)
		// Visible (1 bits) (Default: 0)
		// Host Frame Number LSN (4 bits) (Default: )
	unsigned char BitsGroup_0;

	// Default value: 0
	unsigned char Response_Count;

	// Default value: 0
	unsigned short Entity_ID;

	// Default value: 0.0
	double Range;

	// Default value: 0.0
	double Latitude_X_Offset;

	// Default value: 0.0
	double Longitude_Y_Offset;

	// Default value: 0.0
	double Altitude_Z_Offset;

	// Default value: 0
	unsigned char Red;

	// Default value: 0
	unsigned char Green;

	// Default value: 0
	unsigned char Blue;

	// Default value: 255
	unsigned char Alpha;

	// Default value: 0
	unsigned int Material_Code;

	// Default value: 0.0f
	float Normal_Vector_Azimuth;

	// Default value: 0.0f
	float Normal_Vector_Elevation;

};

//===------------------------------===//
// Factory functions
// 
//===------------------------------===//
inline BasePacket* InstancePacketFromBinaryStream(unsigned char* data, size_t size)
{
	unsigned char id = *( reinterpret_cast<unsigned char*>(data) );
	BasePacket* basepack = 0;
	size_t expectedBytes = 0;
	switch (id)
	{
		case IG_Control::PACKET_ID : expectedBytes = IG_Control::PACKET_SIZE; basepack = new IG_Control; break;
		case Entity_Control::PACKET_ID : expectedBytes = Entity_Control::PACKET_SIZE; basepack = new Entity_Control; break;
		case Conformal_Clamped_Entity_Control::PACKET_ID : expectedBytes = Conformal_Clamped_Entity_Control::PACKET_SIZE; basepack = new Conformal_Clamped_Entity_Control; break;
		case Component_Control::PACKET_ID : expectedBytes = Component_Control::PACKET_SIZE; basepack = new Component_Control; break;
		case Articulated_Part_Control::PACKET_ID : expectedBytes = Articulated_Part_Control::PACKET_SIZE; basepack = new Articulated_Part_Control; break;
		case Short_Articulated_Part_Control::PACKET_ID : expectedBytes = Short_Articulated_Part_Control::PACKET_SIZE; basepack = new Short_Articulated_Part_Control; break;
		case Rate_Control::PACKET_ID : expectedBytes = Rate_Control::PACKET_SIZE; basepack = new Rate_Control; break;
		case Celestial_Sphere_Control::PACKET_ID : expectedBytes = Celestial_Sphere_Control::PACKET_SIZE; basepack = new Celestial_Sphere_Control; break;
		case Atmosphere_Control::PACKET_ID : expectedBytes = Atmosphere_Control::PACKET_SIZE; basepack = new Atmosphere_Control; break;
		case Weather_Control::PACKET_ID : expectedBytes = Weather_Control::PACKET_SIZE; basepack = new Weather_Control; break;
		case View_Control::PACKET_ID : expectedBytes = View_Control::PACKET_SIZE; basepack = new View_Control; break;
		case Sensor_Control::PACKET_ID : expectedBytes = Sensor_Control::PACKET_SIZE; basepack = new Sensor_Control; break;
		case Trajectory_Definition::PACKET_ID : expectedBytes = Trajectory_Definition::PACKET_SIZE; basepack = new Trajectory_Definition; break;
		case View_Definition::PACKET_ID : expectedBytes = View_Definition::PACKET_SIZE; basepack = new View_Definition; break;
		case HAT_HOT_Request::PACKET_ID : expectedBytes = HAT_HOT_Request::PACKET_SIZE; basepack = new HAT_HOT_Request; break;
		case LOS_Segment_Request::PACKET_ID : expectedBytes = LOS_Segment_Request::PACKET_SIZE; basepack = new LOS_Segment_Request; break;
		case LOS_Vector_Request::PACKET_ID : expectedBytes = LOS_Vector_Request::PACKET_SIZE; basepack = new LOS_Vector_Request; break;
		case Start_Of_Frame::PACKET_ID : expectedBytes = Start_Of_Frame::PACKET_SIZE; basepack = new Start_Of_Frame; break;
		case HAT_HOT_Response::PACKET_ID : expectedBytes = HAT_HOT_Response::PACKET_SIZE; basepack = new HAT_HOT_Response; break;
		case HAT_HOT_Extended_Response::PACKET_ID : expectedBytes = HAT_HOT_Extended_Response::PACKET_SIZE; basepack = new HAT_HOT_Extended_Response; break;
		case LOS_Response::PACKET_ID : expectedBytes = LOS_Response::PACKET_SIZE; basepack = new LOS_Response; break;
		case LOS_Extended_Response::PACKET_ID : expectedBytes = LOS_Extended_Response::PACKET_SIZE; basepack = new LOS_Extended_Response; break;
	}
	if ( basepack != 0 )
	{
		size_t ret = basepack->loadFromBinaryStream(data,size);
		if ( ret != expectedBytes )
		{
			delete basepack;
			basepack = 0;
		}
	}
	return basepack;
}
}; // ns Cigi33
#endif

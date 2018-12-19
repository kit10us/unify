// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/Variant.h>
#include <unify/String.h>
#include <unify/Cast.h>

using namespace unify;

Variant::~Variant()
{
	Free();
}

Variant::Variant()
{
	m_type = Type_Undefined;
	data.m_pData = 0;
	Free();
}

Variant::Variant( const Variant & vVar )
{
	*this = vVar;
}

// String Type Constructor...
Variant::Variant( std::string sSource )
{
	data.m_pData = 0;

	Free();
	SetString( sSource );
}

// Integer Type Constructor...
Variant::Variant( const int iSource )
{
	data.m_pData = 0;
	Free();
	SetInt( iSource );
}

// float Type Constructor...
Variant::Variant( const float fSource )
{
	data.m_pData = 0;
	Free();
	SetFloat( fSource );
}

// Variable Type Constructor supporting referencing...
Variant::Variant( void* pData, TYPE type, bool isReference )
{
	data.m_pData = 0;
	m_isConstant = false;

	if( isReference == true )
	{
		data.m_pData = pData;
		m_isReference = true;
		m_type = type;
	} else {
		this->Set( pData, type );
		m_isReference = false;
	}
}


/////////////////////////
// Other types...
/////////////////////////

VarBool::VarBool( const bool bBool ) : Variant( bBool ){}
VarInteger::VarInteger( const int iInt ) : Variant( iInt ){}
VarFloat::VarFloat( const float fFloat ) : Variant( fFloat ){}
VarString::VarString( std::string sString ) : Variant( sString ){}
VarReference::VarReference( void* pData, TYPE type ) : Variant( pData, type, true ){}
VarBoolReference::VarBoolReference( const bool * pBool ) : VarReference( (void*)pBool, Type_Bool ){}
VarIntegerReference::VarIntegerReference( const int * pInt ) : VarReference( (void*)pInt, Type_Integer ){}
VarFloatReference::VarFloatReference( const float * pFloat ) : VarReference( (void*)pFloat, Type_Float ){}
VarStringReference::VarStringReference( const std::string * pString ) : VarReference( (void*)pString, Type_String ){}

const std::string Variant::TypeName( const TYPE type )
{
	switch( type ) 
	{
	default:
	case Type_Undefined: return "Undefined";
	case Type_Bool: return "Bool";
	case Type_Integer: return "Integer";
	case Type_String: return "String";
	case Type_Float: return "float";
	case Type_ByteData: return "ByteData";
	}
}

const Variant::TYPE Variant::TypeEnum( std::string sType )
{
	if( unify::string::StringIs( sType, "BOOL" ) ) return Type_Bool;
	else if( unify::string::StringIs( sType, "INTEGER" ) ) return Type_Integer;
	else if( unify::string::StringIs( sType, "STRING" ) ) return Type_String;
	else if( unify::string::StringIs( sType, "FLOAT" ) ) return Type_Float;
	else if( unify::string::StringIs( sType, "BYTEDATA" ) ) return Type_ByteData;
	else if( unify::string::StringIs( sType, "UNDEFINED" ) ) return Type_Undefined;
	else return Type_Undefined;
}

Variant & Variant::operator=( const Variant & vVar )
{
	Free();

	if( vVar.Reference() ) {
		m_isReference = true;
		data.m_pData = vVar.data.m_pData;
	} else {
		switch( vVar.Type() ) {
			case Type_Undefined:
				break;
			case Type_Bool:
				data.m_pData = new bool( vVar.GeBool() );
				break;
			case Type_Integer:
				data.m_pData = new int( vVar.GetInt() );
				break;
			case Type_String:
				data.m_pString = new std::string( vVar.GetString() );
				break;
			case Type_Float:
				data.m_pData = new float( vVar.GetFloat() );
				break;
			case Type_ByteData:
				break;
		}
	}

	m_type = vVar.Type();
		
	m_isConstant = false; // Assume that we started with a constant but don't want to end up with one (v = constant).
	return *this;
}

void Variant::Free()
{
	if( m_isReference == false && data.m_pData )
	{
		switch( m_type )
		{
		case Type_Bool:
			delete data.m_pBool;
			break;
		case Type_Integer:
			delete data.m_pInt;
			break;
		case Type_String:
			delete data.m_pString;
			break;
		case Type_Float:
			delete data.m_pFloat;
			break;
		default:
			/* ERROR TODO*/
			break;
		}
	}
	data.m_pData = 0;
	m_isReference = false;
	m_type = Type_Undefined;
	m_isConstant = false;
}

// Attempt to resolve a string into a variable.
// Strings need to be wrapped in quotes "string". Else they are considered Resolveable values.
Variant * Variant::Set( std::string sSource )
{
	if( m_isConstant ) return this;

	// Peform standard resolving...

	// Type_Undefined
	if( sSource.empty() ) 
	{
		Free();
		m_type = Type_Undefined;
	}

	// Type_Bool
	if( unify::string::StringIs( sSource, "true" ) ) 
	{
		return this->SetBool( true );
	}
	if( unify::string::StringIs( sSource, "false" ) ) 
	{
		return this->SetBool( false );
	}

	// Type_Integer
	if( unify::string::StringIsInt( sSource ) ) 
	{
		return this->SetInt( unify::Cast< int >( sSource ) );
	}

	// Type_Float
	if( unify::string::StringIsFloat( sSource ) ) 
	{
		return this->SetFloat( unify::Cast< float >( sSource ) );
	}

	// Type_String
	if( sSource[0] == '\"' && sSource[ sSource.length() - 1 ] == '\"' ) 
	{
		return this->SetString( sSource.substr( 1, sSource.length() - 2 ) );
	}
	return 0; // Failure
}

// Pointer to variable
Variant * Variant::Set( const void * pVoid, TYPE type )
{
	if( m_isConstant ) return this;
	Free();
	
	m_type = type;

	switch( type )
	{
	default:
	case Type_Undefined:
		data.m_pData = 0;
		break;

	case Type_Bool:
		data.m_pData = new int( *(int*)pVoid );
		break;

	case Type_Integer:
		data.m_pData = new int( *(int*)pVoid );
		break;

	case Type_String:
		data.m_pString = new std::string( *(std::string*)pVoid );
		break;
	
	case Type_Float:
		data.m_pData = new float( *(float*)pVoid );
		break;
	
	case Type_ByteData:	// Size is valid however
		// Not implemented
		break;
	}
	return this;
}

// Overrides current string (regardless if reference or not)
Variant * Variant::SetReference( void * pVoid, TYPE type )
{
	if( m_isConstant ) return this;
	Free();

	data.m_pData = pVoid;
	m_type = type;
	m_isReference = true;
	return this;
}

Variant * Variant::SetString( std::string sSource )
{
	if( m_isConstant ) return this;

	if( m_isReference ) {
		// Alter reference
		*data.m_pString = sSource;
	} else {
		Free();
		m_type = Type_String;
		data.m_pString = new std::string( sSource );
	}
	return this;
}

Variant * Variant::SetInt( const int iInt )
{
	if( m_isConstant ) return this;

	if( m_isReference ) 
	{
		switch( m_type )
		{
		case Type_Integer:
			*data.m_pInt = iInt;
			break;
		case Type_Bool:
			*data.m_pBool = iInt ? 1 : 0;
			break;
		case Type_String:
			SetString( unify::Cast< std::string >( iInt ) );
			break;
		case Type_Float:
			*data.m_pFloat = (float)iInt;
			break;
		default:
			break;
		};
	} 
	else 
	{
		Free();
		m_type = Type_Integer;
		data.m_pInt = new int( iInt );
	}
	return this;
}

Variant * Variant::SetBool( const bool bBool )
{
	if( m_isConstant ) return this;

	if( m_isReference ) {
		switch( m_type )
		{
		case Type_Integer:
			*data.m_pInt = bBool ? 1 : 0;
			break;
		case Type_Bool:
			*data.m_pBool = bBool;
			break;
		case Type_String:
			SetString( unify::Cast< std::string >( bBool ) );
			break;
		case Type_Float:
			*data.m_pFloat = bBool ? 1.0f : 0.0f;
			break;
		default:
			break;
		};
	} else {
		Free();
		m_type = Type_Bool;
		data.m_pBool = new bool( bBool );
	}
	return this;
}

Variant * Variant::SetFloat( const float fFloat )
{
	if( m_isConstant ) return this;

	if( m_isReference ) {
		switch( m_type )
		{
		case Type_Integer:
			*data.m_pInt = fFloat ? 1 : 0;
			break;
		case Type_Bool:
			*data.m_pBool = fFloat ? true : false;
			break;
		case Type_String:
			SetString( unify::Cast< std::string >( fFloat ) );
			break;
		case Type_Float:
			*data.m_pFloat = fFloat;
			break;
		default:
			break;
		};		
	} else {
		Free();
		m_type = Type_Float;
		data.m_pFloat = new float( fFloat );	
	}
	return this;
}

Variant::TYPE Variant::Type() const
{
	return m_type;
}

std::string Variant::TypeName() const
{
	return TypeName( m_type );
}

bool Variant::GeBool() const
{
	return * data.m_pBool;
}

int Variant::GetInt() const
{
	return( * data.m_pInt );
}

float Variant::GetFloat() const
{
	return( * data.m_pFloat );
}

// Returns a string independant of the original format (will convert).
std::string Variant::GetString() const
{
	switch( m_type ) {
		default:
		case Type_Undefined:
			return "(VarAINT_NULL)";
		case Type_Bool:
			if( *data.m_pBool ) return "true";
			else return "false";
		case Type_Integer:
			return unify::Cast< std::string >( *data.m_pInt );
		case Type_String:
			if( data.m_pString->empty() )
				return "(NULL)";
			return *data.m_pString;
		case Type_Float:
			return unify::Cast< std::string >( *data.m_pFloat );
	}
}

void * Variant::GetAddress() const
{
	return data.m_pData;
}

void Variant::SetConstant( bool isConstant )
{
	m_isConstant = isConstant;
}

bool Variant::Constant() const
{
	return m_isConstant;
}

bool Variant::Reference() const
{
	return m_isReference;
}

const bool Variant::Empty() const
{
	if( data.m_pData == 0 || m_type == Type_Undefined ) return 1;
	return 0;
}

Variant::operator std::string ()
{
	return GetString();
}

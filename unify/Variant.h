// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <map>

namespace unify 
{
	/// <summary>
	/// A variant allowing simple storage and conversion amongst POD types.
	/// </summary>
	class Variant
	{
	public:
		enum TYPE 
		{
			Type_Undefined,
			Type_Bool,
			Type_Integer,
			Type_String,
			Type_Float,
			Type_ByteData
		};
		Variant(); 
		explicit Variant( const Variant & var );
		explicit Variant( const int source );
		explicit Variant( std::string source );
		explicit Variant( const float source );
		Variant( void * pData, TYPE type, bool bReference );
		~Variant();

		Variant & operator=( const Variant & );
		Variant * Set( std::string sSource );
		Variant * Set( const void * pVoid, TYPE type );
		Variant * SetReference( void * pVoid, TYPE type );
		Variant * SetString( std::string sSource );
		Variant * SetInt( const int iInt );
		Variant * SetBool( const bool bBool );
		Variant * SetFloat( const float fFloat );
		TYPE Type() const;
		std::string TypeName() const;
		bool GeBool() const;
		int GetInt() const;
		std::string GetString() const;
		float GetFloat() const;
		void * GetAddress() const;
		void Free();
		void SetConstant( bool bConstant );
		bool Constant() const;
		bool Reference() const;
		const bool Empty() const;
		operator std::string();
		static const std::string TypeName( const TYPE type );
		static const TYPE TypeEnum( std::string sType );

	private:
		TYPE m_type;
		bool m_isReference;	// Is this a reference (if so, we don't handle it's memory).
		bool m_isConstant;	// Can this data be altered from initialization?
		union {
			void * m_pData;
			bool * m_pBool;
			int * m_pInt;
			std::string * m_pString;
			float * m_pFloat;
		} data;
	};

	class VarBool : public Variant
	{public:VarBool( const bool bBool );};

	class VarInteger : public Variant
	{public:VarInteger( const int iInt );};

	class VarFloat : public Variant
	{public:VarFloat( const float fFloat );};

	class VarString : public Variant
	{public:VarString( std::string sString );};

	class VarReference : public Variant
	{public:VarReference( void * pData, TYPE type );};

	class VarBoolReference : public VarReference
	{public:VarBoolReference( const bool * pBool );};

	class VarIntegerReference : public VarReference
	{public:VarIntegerReference( const int * pInt );};

	class VarFloatReference : public VarReference
	{public:VarFloatReference( const float * pFloat );};

	class VarStringReference : public VarReference
	{public:VarStringReference( const std::string * pString );};
} // namespace unify 

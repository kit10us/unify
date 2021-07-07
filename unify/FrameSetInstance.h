/*
 * Unify Library
 * https://github.com/kit10us/unify
 * Copyright (c) 2002, Kit10 Studios LLC
 *
 * This file is part of Unify Library (a.k.a. Unify)
 *
 * Unify is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Unify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Unify.  If not, see <https://www.gnu.org/licenses/>.
 */


#pragma once

#include <unify/Unify.h>
#include <unify/FrameSet.h>
#include <memory>

namespace unify
{
	/// <summary>
	/// A modified FrameSet. Used with animations, separating animation changes into FrameSetInstance, while maintaining the original FrameSet.
	/// </summary>
	class FrameSetInstance
	{
	public:
		typedef std::shared_ptr< FrameSetInstance > ptr;

		FrameSetInstance();
		FrameSetInstance( const FrameSet * frameSet );
		FrameSetInstance( const FrameSetInstance & frameSetInstance );
		~FrameSetInstance();

		FrameSetInstance & operator=( const FrameSetInstance & frameSetInstance );

		const FrameSet * GetFrameSet() const;
		size_t Count() const;
		
		/// <summary>
		/// Reset to FrameSet, or, nullptr, reset to existing FrameSet.
		/// </summary>
		void Reset( const FrameSet * frameSet = nullptr );

		bool Exists( std::string name ) const;
		size_t Find( std::string name ) const;
		const Matrix & Model( size_t index ) const;
		const Matrix & Local( size_t index ) const;
		const Matrix & OriginalModel( size_t ) const;
		const Matrix & OriginalLocal( size_t ) const;
		void Transform( size_t index, const Matrix & transform );
		void UpdateLocals();

	private:
		const FrameSet * m_frameSet;
		std::vector< Matrix > m_models;
		std::vector< Matrix > m_locals; // local = parent * model
		bool m_dirty;
	};
}
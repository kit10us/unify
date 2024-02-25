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

#include <unify/Matrix.h>
#include <map>

namespace unify
{
	///	<summary>
	/// A set of matrices, and connectivity between those matrices, used for mesh animations.
	/// </summary>
	class FrameSet
	{
		friend class FrameSetInstance;
	public:
		class ForEachFunctor
		{
		public:
			virtual ~ForEachFunctor() {}
			virtual void operator()( size_t depth, size_t index ) = 0;
		};


		// Takes ownership...
		FrameSet();
		~FrameSet();

		/// <summary>
		/// Add a matrix with a specified index.
		/// </summary>
		size_t Add( Matrix model, size_t parent, std::string name = std::string() );

		/// <summary>
		/// Check if a matrix exists in our hierarchy. 
		/// Use before calling other functions that reference frames by index to prevent failures.
		/// </summary>
		bool Exists( std::string name ) const;

		/// <summary>
		/// Returns the index of a frame by its name.
		/// </summary>
		size_t Find( std::string name ) const;

		/// <summary>
		/// Returns the count of frames in our hierarchy.
		/// </summary>
		size_t Count() const;

		/// <summary>
		/// Returns the name of a frame at a given index.
		/// </summary>
		std::string Name( size_t index ) const;

		/// <summary>
		/// Returns the model matrix for a given frame.
		/// </summary>
		const Matrix & Model( size_t index ) const;

		/// <summary>
		/// Returns the local matrix for a given frame.
		/// </summary>
		const Matrix & Local( size_t index ) const;

		/// <summary>
		/// Executes a function against all frames.
		/// </summary>
		void ForEach( ForEachFunctor & functor ) const;

	private:
		std::vector< size_t > m_parentIndex;
		std::vector< Matrix > m_models;
		std::vector< Matrix > m_locals; // local = parent * model
		std::map< std::string, size_t > m_nameToIndex;
		std::map< size_t, std::string > m_indexToName;
	};
}
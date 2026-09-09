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

#include <memory>
#include <cstring>
#include <filesystem>
#include <vector>
#include <fstream>
#include <tuple>
#include <memory>
#include <regex>

#include <unify/Unify.h>
#include <unify/String.h>

namespace unify
{
	enum class Slash
	{
		Forward,
		Backward
	};

	/// @brief Split a path, as a string, into a URI prefixm and the actual path.
	/// @param path path with or without URI prefix.
	/// @return a pair of strings with the scheme and the path.
	inline static std::pair<std::string, std::string> URISplit(std::string_view path);	

	/// <summary>
	/// Represents a path, or root identifier (such as a unique definition of an asset, ex. "texture:///", or file, ex/ "file://").
	/// Follows RFC 8089: URI (Uniform Resource Identifier).
	/// </summary>
	/// <note>
	/// Slash directions are not tracked within the path. They must be specified when extracting the full path.
	/// </note>
	class Path	
	{
	public:
		/// @brief Static constructor for a file path.
		/// @return A file path.
		inline static Path MakeFile(std::string_view filename = {});

		Path();

		/// @brief Construct a path from a string, which may or may not have a URI prefix.
		Path(std::string_view path);

		/// @brief Construct a path from a left and right path, combining them.
		/// @note 
		/// The left path's scheme is used if it is present. If not, then the right path's scheme is used if it is present. If neither has a scheme, then the resulting path will not have a scheme. 
		/// If they both have a scheme, then the left path's scheme is used.
		/// @param left 
		/// @param right 
		Path( const Path& left, const Path& right );

		Path(const std::vector< std::string > & pathParts);

		Path(std::string_view scheme, std::string_view path);

		/// @brief Set the URI scheme ("http", "file", etc.).
		bool SetScheme(std::string_view scheme) noexcept;

		/// @brief Get the URI scheme ("http", "file", etc.).
		std::string GetScheme() const noexcept;

		/// @brief Check if the path has a scheme (example: "http", "file").
		bool HasScheme() const noexcept;

		/// @brief Set the path portion ("/home/user", "www.example.com/site", etc.).
		void SetPath(std::string_view path) noexcept;

		/// @brief Get the path portion ("/home/user", "www.example.com/site", etc.).
		std::string GetPath() const noexcept;

		/// @brief Check if path is empty. 
		bool IsEmpty() const noexcept;

		Path & operator=( const Path & path );
		bool operator==( const Path & path ) const;
		bool operator!=( const Path & path ) const;
		Path operator+( const Path & path );
		Path & operator+=( const Path & path );

		/// <summary>
		/// Splits a path into individual parts. If the path begins with a slash, then the first part will be a slash.
		/// </summary>
		std::vector< std::string > Split() const;

		/// <summary>
		/// Joins a vector of path parts, such as that created by Split, into a single path.
		/// </summary>
		Path & Join( const std::vector< std::string > & pathParts );

		/// <summary>
		/// Attempts to normalize the path, resolving all "..".
		/// </summary>
		Path & Normalize();

		bool Exists() const;
		
		Path DirectoryOnly() const;

		/// <summary>
		/// Returns true if a path has any extension.
		/// </summary>
		bool HasExtension() const;

		/// <summary>
		/// Returns the extension from a path, includes the leading dot (.).
		/// Returns empty string if no extension was found.
		/// </summary>
		std::string ExtensionOnly() const;

		/// <summary>
		/// Returns the file name (e.g., "c:\folder\filename.ext" ... "filename.ext" )
		/// Equivalent to: boost::filesystem::path.filename
		/// </summary>
		std::string Filename() const;

		/// <summary>
		/// Returns the file name without extension (e.g., "c:\folder\filename.ext" ... "filename" )
		/// Equivalent to: boost::filesystem::path.stem
		/// </summary>
		std::string FilenameNoExtension() const;

		Path & Combine( const Path & left, const Path & right );

		bool IsDirectory() const;

		bool IsExtension( std::string extension ) const;

		void ChangeExtension( std::string extension );

		// Equivalent to Combine( DirectoryOnly( pathIn ), Filename( newFilename ) )
		Path & ChangeFilename( const Path & newFilename );

		/// <summary>
		/// Returns a string representation of the path maintaining the original slash directions."
		/// </summary>
		std::string ToString() const noexcept;

		/// <summary>
		/// Returns a string with all slashes in a uniform direction.
		/// </summary>
		std::string ToString( Slash direction ) const noexcept;

		/// <summary>
		/// Returns a wide string representation of the path maintaining the original slash directions."
		/// </summary>
		std::wstring ToWString() const;

		/// <summary>
		/// Returns a wide string with all slashes in a uniform direction.
		/// </summary>
		std::wstring ToWString( Slash direction ) const;

		/// <summary>
		/// Returns an XPath string representation of the path maintaining the original slash directions."
		/// </summary>
		std::string ToXPath() const;

		/// <summary>
		/// Returns a wide string representation of the path, in XPath format, maintaining the original slash directions."
		/// </summary>
		std::wstring ToWXPath() const;

		/// <summary>
		/// Returns a wide string with all slashes in a uniform direction, in XPath format.
		/// </summary>
		std::wstring ToWXPath( Slash direction ) const;

		/// <summary>
		/// Returns a stl file path.
		/// </summary>
		std::filesystem::path ToPath() const;

		/// <summary>
		/// Delete a path.
		/// </summary>
		bool Delete();

		/// <summary>
		/// Rename a path.
		/// </summary>
		bool Rename( unify::Path to );

		/// <summary>
		/// Returns a list of files in this paths directory.
		/// If the path is not a directory, it returns the current file.
		/// </summary>
		std::vector<Path> Files() const;

	private:
		std::string m_scheme;
		std::string m_path;
	};

	/// <summary>
	/// Return a path with a different extension.
	/// </summary>
	Path ChangeExtension( Path path, std::string extension );
	
	inline std::pair<std::string, std::string> URISplit(std::string_view path)
	{
		std::regex pattern { "^([A-Za-z0-9]+)://(.*)$" };
		std::match_results<std::string_view::const_iterator> match{};
		std::regex_search(path.begin(), path.end(), match, pattern);
		return {match[1], match[2]};
	}

	inline Path Path::MakeFile(std::string_view file_path)
	{ 
		return unify::Path{"file", file_path};
	}
}

std::ostream & operator<<( std::ostream & os, const unify::Path & path );

#include <unify/Path.inl>
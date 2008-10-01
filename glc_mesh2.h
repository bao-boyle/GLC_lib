/****************************************************************************

 This file is part of the GLC-lib library.
 Copyright (C) 2005-2008 Laurent Ribon (laumaya@users.sourceforge.net)
 Version 1.0.0, packaged on August, 2008.

 http://glc-lib.sourceforge.net

 GLC-lib is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 GLC-lib is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with GLC-lib; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*****************************************************************************/

//! \file glc_mesh2.h interface for the GLC_Mesh2 class.

#ifndef GLC_MESH2_H_
#define GLC_MESH2_H_
#include <QHash>
#include <QVector>
#include <QList>

#include "glc_material.h"
#include "glc_vbogeom.h"
#include "glc_vector2df.h"
#include "glc_vector3df.h"

// TODO a supprimer
typedef QHash<int, GLC_Vector3df> Vector3dHash;
typedef QHash<int, GLC_Vector2df> Vector2dHash;
// Fin a supprimer

typedef QHash<GLC_uint, GLC_Material*> MaterialHash;
typedef QList<GLC_Vertex> VertexVector;
typedef QList<GLuint> IndexVector;
typedef QHash<GLC_uint, IndexVector*> MaterialGroup;

enum FaceType
{
	notSet,
	coordinate,
	coordinateAndTexture,
	coordinateAndNormal,
	coordinateAndTextureAndNormal
};

//////////////////////////////////////////////////////////////////////
//! \class GLC_Mesh2
/*! \brief GLC_Mesh2 : OpenGL 3D Mesh*/

/*! An GLC_Mesh2 is Mesh composed of polygons
 * 		- Each polygon must be a planar Face
 * 		- Each face is composed by vertexs
 * */
//////////////////////////////////////////////////////////////////////
class GLC_Mesh2 : public GLC_VboGeom
{
//////////////////////////////////////////////////////////////////////
/*! @name Constructor / Destructor */
//@{
//////////////////////////////////////////////////////////////////////
public:
	//! Construct an empty Mesh
	explicit GLC_Mesh2();
	
	//! Copy constructor
	explicit GLC_Mesh2(const GLC_Mesh2 &meshToCopy);
	
	//! Delete Mesh's faces and clear faces list
	virtual ~GLC_Mesh2(void);
//@}

//////////////////////////////////////////////////////////////////////
/*! \name Get Functions*/
//@{
//////////////////////////////////////////////////////////////////////
public:
	//! Get number of faces
	inline unsigned int getNumberOfFaces() const {return m_NumberOfFaces;}
	//! Get number of vertex
	inline unsigned int getNumberOfVertex() const {return m_Vertex.size();}
	//! return a vertex with key
	inline const GLC_Vector3df getVertex(const int key) const
	{
		return GLC_Vector3df(m_Vertex[key].x, m_Vertex[key].y, m_Vertex[key].z);
	}
	//! Get number of submaterial
	inline unsigned int getNumberOfSubMaterial() const {return m_MaterialHash.size();}
	//! Get specified mesh sub material
	inline GLC_Material* getSubMaterial(const GLC_uint key) {return m_MaterialHash[key];}
	//! return true if Material key is in the mesh
	inline const bool containsMaterial(const GLC_uint key) const {return m_MaterialHash.contains(key);}
	//! Return material index if Material is the same than a material already in the mesh
	/*! Return -1 if the material is not found
	 */
	GLC_uint materialIndex(const GLC_Material& mat) const;
	//! return the mesh bounding box
	virtual GLC_BoundingBox* getBoundingBox(void) const;
	//! Return a copy of the geometry
	virtual GLC_VboGeom* clone() const;

//@}

//////////////////////////////////////////////////////////////////////
/*! \name Set Functions*/
//@{
//////////////////////////////////////////////////////////////////////
public:
	//! Add material to mesh
	void addMaterial(GLC_uint Index, GLC_Material *);
	
	//! Add triangles with the same material to the mesh
	void addTriangles(const VertexVector &, GLC_Material*);

	//! Reverse mesh normal
	void reverseNormal();
	 
//@}

//////////////////////////////////////////////////////////////////////
/*! \name OpenGL Functions*/
//@{
//////////////////////////////////////////////////////////////////////
public:
	//! Specific glExecute method
	virtual void glExecute(bool, bool forceWire= false);

private:

	//! if the geometry have a texture, load it
	virtual void glLoadTexture(void);
	
	//! Virtual interface for OpenGL Geometry set up.
	/*! This Virtual function is implemented here.\n
	 *  Throw GLC_OpenGlException*/
	virtual void glDraw(void);
	
//@}

//////////////////////////////////////////////////////////////////////
//! Private services Functions
//////////////////////////////////////////////////////////////////////
private:
		
	
//////////////////////////////////////////////////////////////////////
// Private members
//////////////////////////////////////////////////////////////////////
private:
	
	//! Vertexs
	VertexVector m_Vertex;
	//! Hash table of Vector Index grouped by material
	MaterialGroup m_MaterialGroup;
	
	//! Material Hash table
	MaterialHash m_MaterialHash;
	
	//! Mesh number of faces
	unsigned int m_NumberOfFaces;
		
	//! Selection state
	bool m_IsSelected;
	
};
#endif //GLC_MESH2_H_

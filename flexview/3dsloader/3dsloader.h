/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli <info@spacesimulator.net>
 *
 * ALL RIGHTS RESERVED
 *
 *
 * Tutorial 4: 3d engine - 3ds models loader
 * 
 * Include File: 3dsloader.cpp
 *  
 */

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
//#include <io.h>
#include <sys/stat.h>
#include "mat_vect.h"
#include "load_bmp.h"



#define MAX_VERTICES 60000 // Max number of vertices (for each object)
#define MAX_POLYGONS 60000 // Max number of polygons (for each object)




/**********************************************************
 *
 * TYPES DECLARATION
 *
 *********************************************************/

class Object3ds
{
	
public:

 Object3ds();
~Object3ds();

int ObjLoad(char *p_object_name, char *p_texture_name);

void render(float * position, float scale, int ShadeModel, int model, int normals);
int GetInfo(int param);
char * GetName();
int HasTexture;

private:

//Vertex
typedef struct{
    float x,y,z;
}vertex_type;
// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct{
    int a,b,c;
}polygon_type;
// The mapcoord type, 2 texture coordinates for each vertex
typedef struct{
    float u,v;
}mapcoord_type;

// The object type

typedef struct {

	char name[20]; // Name of the object
    
	int vertices_qty; // Number of vertices
    int polygons_qty; // Number of polygons
	int size;// aprox size of the model

    vertex_type vertex[MAX_VERTICES]; // Array of vertices
    vertex_type normal[MAX_VERTICES]; // Array of the vertices' normals



    polygon_type polygon[MAX_POLYGONS]; // Array of polygons (numbers that point to the vertices' list)
    mapcoord_type mapcoord[MAX_VERTICES]; // Array of U,V coordinates for texture mapping

    int id_texture; // Number of the texture 

} obj_type, *obj_type_ptr;

obj_type object; 


char Load3DS(obj_type_ptr p_object, char *p_filename);
void ObjCalcNormals(obj_type_ptr p_object);




};
//*************************************************************************************************************

/**********************************************************
 *
 * FUNCTION ObjLoad(char *p_object_name, char *p_texture_name)
 *
 * This function loads an object and set some object's data
 *
 * Parameters: p_object_name = object name
 *			   p_texture_name = texture name
 *             p_pos_x = starting position x coordinate
 *             p_pos_y = starting position y coordinate
 *             p_pos_z = starting position z coordinate
 *             p_rot_x = starting orientation x axis
 *             p_rot_y = starting orientation y axis
 *             p_rot_z = starting orientation z axis
 *
 * Return value: (char) 1 if the object was loaded correctly, 0 otherwise
 *
 *********************************************************/
Object3ds::Object3ds()
{
    
}

Object3ds::~Object3ds()
{
object.size=0;

}

int Object3ds::GetInfo(int param)
{
	switch (param)
	{
		case 1:return object.polygons_qty;break;
		case 2:return object.vertices_qty;break;	
		case 3:return object.size;break;
	}
        return -1;
}

char * Object3ds::GetName()
{
	return (object.name);
}

int Object3ds::ObjLoad(char *p_object_name, char *p_texture_name)
{
	
	object.polygons_qty=0;
	object.vertices_qty=0;
	object.size=0;

    if (Load3DS (&object,p_object_name)==0) return(0); //Object loading
    object.id_texture=LoadBMP(p_texture_name); // The Function LoadBitmap() returns the current texture ID
	if (object.id_texture==-1 )HasTexture=0;
	else HasTexture=1;
	ObjCalcNormals(&object); //Once we have all the object data we need to calculate all the normals of the object's vertices
	return (1); // If all is ok then return 1
}

/**********************************************************
 *
 * SUBROUTINE ObjCalcNormals(obj_type_ptr p_object)
 *
 * This function calculate all the polygons and vertices' normals of the specified object
 *
 * Input parameters: p_object = object
 *
 *********************************************************/
void Object3ds::ObjCalcNormals(obj_type_ptr p_object)
{
	int i;
	p3d_type l_vect1,l_vect2,l_vect3,l_vect_b1,l_vect_b2,l_normal;  //Some local vectors
	int l_connections_qty[MAX_VERTICES]; //Number of poligons around each vertex

    // Resetting vertices' normals...
	for (i=0; i<p_object->vertices_qty; i++)
	{
		p_object->normal[i].x = 0.0;
		p_object->normal[i].y = 0.0;
		p_object->normal[i].z = 0.0;
		l_connections_qty[i]=0;
	}
	
	for (i=0; i<p_object->polygons_qty; i++)
	{
        l_vect1.x = p_object->vertex[p_object->polygon[i].a].x;
        l_vect1.y = p_object->vertex[p_object->polygon[i].a].y;
        l_vect1.z = p_object->vertex[p_object->polygon[i].a].z;
        l_vect2.x = p_object->vertex[p_object->polygon[i].b].x;
        l_vect2.y = p_object->vertex[p_object->polygon[i].b].y;
        l_vect2.z = p_object->vertex[p_object->polygon[i].b].z;
        l_vect3.x = p_object->vertex[p_object->polygon[i].c].x;
        l_vect3.y = p_object->vertex[p_object->polygon[i].c].y;
        l_vect3.z = p_object->vertex[p_object->polygon[i].c].z;         
  
        // Polygon normal calculation
		VectCreate (&l_vect1, &l_vect2, &l_vect_b1); // Vector from the first vertex to the second one
        VectCreate (&l_vect1, &l_vect3, &l_vect_b2); // Vector from the first vertex to the third one
        VectDotProduct (&l_vect_b1, &l_vect_b2, &l_normal); // Dot product between the two vectors
        VectNormalize (&l_normal); //Normalizing the resultant we obtain the polygon normal

		l_connections_qty[p_object->polygon[i].a]+=1; // For each vertex shared by this polygon we increase the number of connections
		l_connections_qty[p_object->polygon[i].b]+=1;
		l_connections_qty[p_object->polygon[i].c]+=1;

		p_object->normal[p_object->polygon[i].a].x+=l_normal.x; // For each vertex shared by this polygon we add the polygon normal
		p_object->normal[p_object->polygon[i].a].y+=l_normal.y;
		p_object->normal[p_object->polygon[i].a].z+=l_normal.z;
		p_object->normal[p_object->polygon[i].b].x+=l_normal.x;
		p_object->normal[p_object->polygon[i].b].y+=l_normal.y;
		p_object->normal[p_object->polygon[i].b].z+=l_normal.z;
		p_object->normal[p_object->polygon[i].c].x+=l_normal.x;
		p_object->normal[p_object->polygon[i].c].y+=l_normal.y;
		p_object->normal[p_object->polygon[i].c].z+=l_normal.z;	
	}	
	
    for (i=0; i<p_object->vertices_qty; i++)
	{
		if (l_connections_qty[i]>0)
		{
			p_object->normal[i].x /= l_connections_qty[i]; // Let's now average the polygons' normals to obtain the vertex normal!
			p_object->normal[i].y /= l_connections_qty[i];
			p_object->normal[i].z /= l_connections_qty[i];
		}
	}
}

static int filelength(int no)
{
    struct stat f_stat;
    fstat(no, &f_stat);
    return f_stat.st_size;
}

/**********************************************************
 *
 * FUNCTION Load3DS(obj_type_ptr p_object, char *p_filename)
 *
 * This function loads a mesh from a 3ds file.
 * Please note that we are loading only the vertices, polygons and mapping lists.
 * If you need to load meshes with advanced features as for example: 
 * multi objects, materials, lights and so on, you must insert other chunk parsers.
 *
 * Input parameters: p_object = Pointer to the Object
 *					 p_filename = Filename of the object to load
 *
 * Return value: (char) 1 if the object was loaded correctly, 0 otherwise
 *
 *********************************************************/
char Object3ds::Load3DS(obj_type_ptr p_object, char *p_filename)
{
	int i; //Index variable
        int r;
	
	FILE *l_file; //File pointer
	
	unsigned short l_chunk_id; //Chunk identifier
	unsigned int l_chunk_length; //Chunk length

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk

	unsigned short l_face_flags; //Flag that stores some face information

	if (p_filename=='\0') return(0);

	if ((l_file=fopen (p_filename, "rb"))== NULL) 
	{
       // MessageBox(NULL,"3DS file not found","Spacesim",MB_OK | MB_ICONERROR);
		return (0);
	}

	while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file 
	{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

                int r = fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
		printf("ChunkID: %x\n",l_chunk_id); 
                r = fread (&l_chunk_length, 4, 1, l_file); //Read the length of the chunk
		printf("ChunkLength: %x\n",l_chunk_length);
                (void)r;

		switch (l_chunk_id)
        {
			//----------------- MAIN3DS -----------------
			// Description: Main chunk, contains all the other chunks
			// Chunk ID: 4d4d 
			// Chunk Length: 0 + sub chunks
			//-------------------------------------------
			case 0x4d4d: 
			break;    

			//----------------- EDIT3DS -----------------
			// Description: 3D Editor chunk, objects layout info 
			// Chunk ID: 3d3d (hex)
			// Chunk Length: 0 + sub chunks
			//-------------------------------------------
			case 0x3d3d:
			break;
			
			//--------------- EDIT_OBJECT ---------------
			// Description: Object block, info for each object
			// Chunk ID: 4000 (hex)
			// Chunk Length: len(object name) + sub chunks
			//-------------------------------------------
			case 0x4000: 
				i=0;
				do
				{
                                        int r = fread (&l_char, 1, 1, l_file);
                    p_object->name[i]=l_char;
					i++;
                                        (void)r;
                }while(l_char != '\0' && i<20);
			break;

			//--------------- OBJ_TRIMESH ---------------
			// Description: Triangular mesh, contains chunks for 3d mesh info
			// Chunk ID: 4100 (hex)
			// Chunk Length: 0 + sub chunks
			//-------------------------------------------
			case 0x4100:
			break;
			
			//--------------- TRI_VERTEXL ---------------
			// Description: Vertices list
			// Chunk ID: 4110 (hex)
			// Chunk Length: 1 x unsigned short (number of vertices) 
			//             + 3 x float (vertex coordinates) x (number of vertices)
			//             + sub chunks
			//-------------------------------------------
			case 0x4110: 
                                r = fread (&l_qty, sizeof (unsigned short), 1, l_file);
                p_object->vertices_qty = l_qty;
                printf("Number of vertices: %d\n",l_qty);
				if (l_qty>MAX_VERTICES) 
				{
			       // MessageBox(NULL,"Number of vertices too high","Spacesim",MB_OK | MB_ICONERROR);
					return (0);
				}
                for (i=0; i<l_qty; i++)
                {
                                        r = fread (&p_object->vertex[i].x, sizeof(float), 1, l_file);
 					printf("Vertices list x: %f\n",p_object->vertex[i].x);
                    r = fread (&p_object->vertex[i].y, sizeof(float), 1, l_file);
 					printf("Vertices list y: %f\n",p_object->vertex[i].y);
                                        r = fread (&p_object->vertex[i].z, sizeof(float), 1, l_file);
 					printf("Vertices list z: %f\n",p_object->vertex[i].z);

					if(p_object->vertex[i].x> object.size) object.size = p_object->vertex[i].x;
					if(p_object->vertex[i].y> object.size) object.size = p_object->vertex[i].y;
					if(p_object->vertex[i].z> object.size) object.size = p_object->vertex[i].z;

				}
				break;

			//--------------- TRI_FACEL1 ----------------
			// Description: Polygons (faces) list
			// Chunk ID: 4120 (hex)
			// Chunk Length: 1 x unsigned short (number of polygons) 
			//             + 3 x unsigned short (polygon points) x (number of polygons)
			//             + sub chunks
			//-------------------------------------------
			case 0x4120:
                                r = fread (&l_qty, sizeof (unsigned short), 1, l_file);
                p_object->polygons_qty = l_qty;
                printf("Number of polygons: %d\n",l_qty); 
				if (l_qty>MAX_POLYGONS) 
				{
			        //MessageBox(NULL,"Number of polygons too high","Spacesim",MB_OK | MB_ICONERROR);
					return (0);
				}				
                for (i=0; i<l_qty; i++)
                {
                                        r = fread (&p_object->polygon[i].a, sizeof (unsigned short), 1, l_file);
					printf("Polygon point a: %d\n",p_object->polygon[i].a);
                                        r = fread (&p_object->polygon[i].b, sizeof (unsigned short), 1, l_file);
					printf("Polygon point b: %d\n",p_object->polygon[i].b);
                                        r = fread (&p_object->polygon[i].c, sizeof (unsigned short), 1, l_file);
					printf("Polygon point c: %d\n",p_object->polygon[i].c);
                                        r = fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
					printf("Face flags: %x\n",l_face_flags);
				}
                break;

			//------------- TRI_MAPPINGCOORS ------------
			// Description: Vertices list
			// Chunk ID: 4140 (hex)
			// Chunk Length: 1 x unsigned short (number of mapping points) 
			//             + 2 x float (mapping coordinates) x (number of mapping points)
			//             + sub chunks
			//-------------------------------------------
			case 0x4140:
                                r = fread (&l_qty, sizeof (unsigned short), 1, l_file);
				for (i=0; i<l_qty; i++)
				{
                                        r = fread (&p_object->mapcoord[i].u, sizeof (float), 1, l_file);
					printf("Mapping list u: %f\n",p_object->mapcoord[i].u);
                    r = fread (&p_object->mapcoord[i].v, sizeof (float), 1, l_file);
					printf("Mapping list v: %f\n",p_object->mapcoord[i].v);
				}
                break;

			//----------- Skip unknow chunks ------------
			//We need to skip all the chunks that currently we don't use
			//We use the chunk length information to set the file pointer
			//to the same level next chunk
			//-------------------------------------------
			default:
				 fseek(l_file, l_chunk_length-6, SEEK_CUR);
        } 
	}
	fclose (l_file); // Closes the file stream
        (void)r;
	return (1); // Returns ok
}

void Object3ds::render(float * position, float scale, int ShadeModel, int model, int normals)
{

	if(HasTexture)	glEnable(GL_TEXTURE_2D);
	else glDisable(GL_TEXTURE_2D);

    glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);

	glPushMatrix();
	glTranslatef(position[0],position[1],position[2]);
	glScalef(scale,scale,scale);

    if(ShadeModel==1) glShadeModel(GL_FLAT);
	else glShadeModel(GL_SMOOTH);
    
    
    if(model==0) glPolygonMode (GL_FRONT, GL_FILL);
	else if(model==1) glPolygonMode (GL_FRONT, GL_LINE);
	else  if(model==2) glPolygonMode (GL_FRONT, GL_POINT);
	glLineWidth(0);

  	glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)

	for (int j=0;j<object.polygons_qty ;j++)
	{
	
		//----------------- FIRST VERTEX -----------------
		//Normal coordinates of the first vertex
		glNormal3f( object.normal[ object.polygon[j].a ].x,
					object.normal[ object.polygon[j].a ].y,
					object.normal[ object.polygon[j].a ].z);        

		// Texture coordinates of the first vertex
		glTexCoord2f( object.mapcoord[ object.polygon[j].a ].u, object.mapcoord[ object.polygon[j].a ].v);
		// Coordinates of the first vertex
		glVertex3f( object.vertex[ object.polygon[j].a ].x,
					object.vertex[ object.polygon[j].a ].y,
					object.vertex[ object.polygon[j].a ].z);

		//----------------- SECOND VERTEX -----------------
		//Normal coordinates of the second vertex
		glNormal3f( object.normal[ object.polygon[j].b ].x,
					object.normal[ object.polygon[j].b ].y,
					object.normal[ object.polygon[j].b ].z);
		// Texture coordinates of the second vertex
		glTexCoord2f( object.mapcoord[ object.polygon[j].b ].u,object.mapcoord[ object.polygon[j].b ].v);
		// Coordinates of the second vertex
		glVertex3f( object.vertex[ object.polygon[j].b ].x,
					object.vertex[ object.polygon[j].b ].y,
					object.vertex[ object.polygon[j].b ].z);
        		//----------------- THIRD VERTEX -----------------
		//Normal coordinates of the third vertex
		glNormal3f( object.normal[ object.polygon[j].c ].x,
					object.normal[ object.polygon[j].c ].y,
					object.normal[ object.polygon[j].c ].z);
		// Texture coordinates of the third vertex
		glTexCoord2f( object.mapcoord[ object.polygon[j].c ].u,object.mapcoord[ object.polygon[j].c ].v);
		// Coordinates of the Third vertex
		glVertex3f( object.vertex[ object.polygon[j].c ].x,
					object.vertex[ object.polygon[j].c ].y,
					object.vertex[ object.polygon[j].c ].z);
	}
	glEnd();   
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
        (void)normals;
}
//**************************************************************************************************************


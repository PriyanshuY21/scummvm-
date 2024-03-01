/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef FREESCAPE_GFX_OPENGL_H
#define FREESCAPE_GFX_OPENGL_H

#include "graphics/opengl/system_headers.h"
#include "math/vector3d.h"
#include "math/vector2d.h"

#include "freescape/gfx.h"

#ifdef USE_OPENGL_GAME

namespace Freescape {

class OpenGLRenderer : public Renderer {
public:
	OpenGLRenderer(int screenW, int screenH, Common::RenderMode renderMode);
	virtual ~OpenGLRenderer();

	struct Vertex {
		GLfloat x;
		GLfloat y;
		GLfloat z;
	};

	void copyToVertexArray(uint idx, const Math::Vector3d &src) {
		assert(idx < kVertexArraySize);
		_verts[idx].x = src.x(); _verts[idx].y = src.y(); _verts[idx].z = src.z();
	}

	Vertex *_verts;

	struct Coord {
		GLfloat x;
		GLfloat y;
	};

	Coord *_coords;

	void copyToCoordArray(uint idx, const Math::Vector2d &src) {
		assert(idx < kCoordsArraySize);
		_coords[idx].x = src.getValue(0); _coords[idx].y = src.getValue(1);
	}

	GLubyte _defaultStippleArray[128] = {
		0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
		0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
		0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
		0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
		0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
		0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
		0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
		0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
		0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
		0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
		0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
		0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
		0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
		0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
		0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
		0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
	};

	GLubyte *_variableStippleArray;

	virtual void init() override;
	virtual void clear(uint8 r, uint8 g, uint8 b, bool ignoreViewport = false) override;
	virtual void setViewport(const Common::Rect &rect) override;
	virtual Common::Point nativeResolution() override;
	virtual void positionCamera(const Math::Vector3d &pos, const Math::Vector3d &interest) override;
	virtual void updateProjectionMatrix(float fov, float nearClipPlane, float farClipPlane) override;

	virtual void useColor(uint8 r, uint8 g, uint8 b) override;
	virtual void polygonOffset(bool enabled) override;
	virtual void setStippleData(byte *data) override;
	virtual void useStipple(bool enabled) override;


	Texture *createTexture(const Graphics::Surface *surface) override;
	void freeTexture(Texture *texture) override;
	virtual void drawTexturedRect2D(const Common::Rect &screenRect, const Common::Rect &textureRect, Texture *texture) override;

	virtual void renderSensorShoot(byte color, const Math::Vector3d sensor, const Math::Vector3d player, const Common::Rect viewPort) override;
	virtual void renderPlayerShootBall(byte color, const Common::Point position, int frame, const Common::Rect viewPort) override;
	virtual void renderPlayerShootRay(byte color, const Common::Point position, const Common::Rect viewPort) override;
	virtual void renderCrossair(const Common::Point crossairPosition) override;

	virtual void renderFace(const Common::Array<Math::Vector3d> &vertices) override;

	virtual void flipBuffer() override;
	virtual void drawFloor(uint8 color) override;
	void drawCelestialBody(Math::Vector3d position, float radius, uint8 color) override;

	virtual Graphics::Surface *getScreenshot() override;
};

} // End of namespace Freescape

#endif

#endif // FREESCAPE_GFX_OPENGL_H
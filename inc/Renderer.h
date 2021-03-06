#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcommon.h>

#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <WICTextureLoader.h>
#include <SpriteFont.h>
#include <PrimitiveBatch.h>
#include <d3dcompiler.h>

#include "common_include.h"
#include "media.h"
#include "Vertex.h"
#include "Camera3D.h"

#include "Timer.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

namespace Core
{
	enum SHADER_TYPE
	{
		SHADER_TYPE_NONE = 0,
		SHADER_TYPE_COLOR,
		SHADER_TYPE_TEXTURE,
	};

	enum TRANSFORM_TYPE : UINT
	{
		TRANSFORM_WORLD,
		TRANSFORM_PROJECTION,
		TRANSFORM_VIEW,
	};

	class Renderer
	{

	private:
		HWND hWnd;
		
		int bbWidth, bbHeight;
		SHADER_TYPE boundShader;

		IDXGIFactory *factory;
		IDXGIAdapter *adapter;
		IDXGISwapChain *swapChain;
		ID3D11Device *device;
		ID3D11DeviceContext *context;
		ID3D11RenderTargetView *RTView;
	    DirectX::SpriteBatch *SBatch;
	    DirectX::SpriteFont *SFont;

		ID3D11InputLayout *textureInputLayout;

		ID3D11VertexShader *textureVShader;
		ID3D11PixelShader *texturePShader;

		ID3D11VertexShader *colorVShader;
		ID3D11PixelShader *colorPShader;
		ID3D11InputLayout *colorInputLayout;
		ID3D11Buffer *colorCBuffer;

		Matrix worldMat;
		Matrix projMat;
		Matrix viewMat;
		Matrix invWorldMat;
		Matrix invProjMat;
		Matrix invViewMat;
		ID3D11Buffer *worldCBuffer;
		ID3D11Buffer *viewCBuffer;
		ID3D11Buffer *projectionCBuffer;
		
		Camera3D camera;

		ID3D11RasterizerState *rsDisableCull;
		ID3D11RasterizerState *rsCullFront;
		ID3D11RasterizerState *rsDefault; //default rasterizer state with back-face culling
		
		ID3D11SamplerState *defaultSampler;

		ID3D11DepthStencilState *depthStencilEnabled; 
		ID3D11DepthStencilState *depthStencilDisabled;


		//debug draw stuff----------------------------

		//camera stuff
		/*Matrix rotation;
		Vector3 translation;*/

	public:
		Renderer();
		~Renderer();

		bool Init(const RECT &windowRect, HWND hWnd);

		void BeginRender(void);
		void EndRender(void);

		void BindShader(SHADER_TYPE type);
		void UnbindShader(void);

		//bind the default texture sampler to the pipeline at slot 0
		void BindSampler(bool bind);

		int GetBBWidth(void) const  { return this->bbWidth; }
		int GetBBHeight(void) const { return this->bbHeight; }

		SHADER_TYPE GetBoundShader(void) const { return this->boundShader; }
		
		void SetColor(const Vector4 &color);

		void SetTransform(TRANSFORM_TYPE type, const Matrix &val);
		Matrix GetTransform(TRANSFORM_TYPE type) const;
		Matrix GetInvTransform(TRANSFORM_TYPE type) const; //invert the result of multiplying all matrices on the matrix stack
		
		Camera3D &GetCamera(void) { return this->camera; }
		void SetCullMode(D3D11_CULL_MODE mode);
		void SetDepthStencilEnabled(bool enable);

		void BeginText(void);
		void RenderText(const std::wstring &txt, float screenPosX, float screenPosY);
		void EndText(void);

		IDXGIFactory *const GetFactory(void) { return this->factory; }
		IDXGIAdapter *const GetAdapter(void) { return this->adapter; }
		IDXGISwapChain *const GetSwapChain(void) { return this->swapChain; }
		ID3D11Device *const GetDevice(void) { return this->device; }
		ID3D11DeviceContext *const GetDeviceContext(void) { return this->context; }
		ID3D11RenderTargetView *const GetRTView(void) { return this->RTView; }
		DirectX::SpriteBatch *const GetSpriteBatch(void) { return this->SBatch; }
		DirectX::SpriteFont *const GetSpriteFont(void) {return this->SFont; }
		ID3D11SamplerState *const GetSamplerState(void) { return this->defaultSampler; }

	private:

		bool createCBuffers(void);
		bool createShadersAndInputLayouts(void);
		bool createSamplers(void);
		bool createRasterizerStates(void);

		void rebindTransformCBs(void);
	};
}
#endif


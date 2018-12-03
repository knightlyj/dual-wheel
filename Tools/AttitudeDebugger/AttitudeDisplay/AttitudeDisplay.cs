using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SharpDX;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;
using SharpDX.DXGI;
using Buffer = SharpDX.Direct3D11.Buffer;
using Device = SharpDX.Direct3D11.Device;
using SharpDX.WIC;

namespace AttitudeDisplay
{
    public partial class AttitudeDisplay : UserControl
    {
        public AttitudeDisplay()
        {
            InitializeComponent();

            D3D11_Init();
        }

        Device d3dDevice;
        SwapChain swapChain;
        RenderTargetView renderTargetView;
        Texture2D depthStencil;
        DepthStencilView depthStencilView;
        Buffer vertexBuffer;
        Buffer indexBuffer;
        Buffer viewMatBuffer;
        Buffer projMatBuffer;
        Buffer rotMatBuffer;
        ShaderResourceView textureRV;
        SamplerState samplerLinear;
        VertexShader vertexShader;
        PixelShader pixelShader;
        Matrix viewMat;
        Matrix projMat;
        Matrix rotMat;

        void D3D11_Init()
        {
            SwapChainDescription sd = new SwapChainDescription();
            sd.BufferCount = 1;
            sd.ModeDescription.Width = 512;
            sd.ModeDescription.Height = 512;
            sd.ModeDescription.Format = Format.B8G8R8A8_UNorm;
            sd.ModeDescription.RefreshRate.Numerator = 60;
            sd.ModeDescription.RefreshRate.Denominator = 1;
            sd.Usage = Usage.RenderTargetOutput;
            sd.OutputHandle = Handle;
            sd.SampleDescription.Count = 1;
            sd.SampleDescription.Quality = 0;
            sd.IsWindowed = true;

            DeviceCreationFlags devCreateFlag = DeviceCreationFlags.None;
#if DEBUG
            devCreateFlag = DeviceCreationFlags.Debug;
#endif

            Device.CreateWithSwapChain(DriverType.Hardware, devCreateFlag, sd, out d3dDevice, out swapChain);

            Texture2D backBuffer;
            backBuffer = swapChain.GetBackBuffer<Texture2D>(0);
            renderTargetView = new RenderTargetView(d3dDevice, backBuffer);

            backBuffer.Dispose();

            Texture2DDescription descDepth = new Texture2DDescription();
            descDepth.Width = 512;
            descDepth.Height = 512;
            descDepth.MipLevels = 1;
            descDepth.ArraySize = 1;
            descDepth.Format = Format.D24_UNorm_S8_UInt;
            descDepth.SampleDescription.Count = 1;
            descDepth.SampleDescription.Quality = 0;
            descDepth.Usage = ResourceUsage.Default;
            descDepth.BindFlags = BindFlags.DepthStencil;
            descDepth.CpuAccessFlags = 0;
            descDepth.OptionFlags = 0;

            depthStencil = new Texture2D(d3dDevice, descDepth);

            DepthStencilViewDescription descDSV = new DepthStencilViewDescription();
            descDSV.Format = descDepth.Format;
            descDSV.Dimension = DepthStencilViewDimension.Texture2D;
            descDSV.Texture2D.MipSlice = 0;

            depthStencilView = new DepthStencilView(d3dDevice, depthStencil, descDSV);

            d3dDevice.ImmediateContext.OutputMerger.SetRenderTargets(depthStencilView, renderTargetView);

            Viewport vp;
            vp.Width = 512;
            vp.Height = 512;
            vp.MinDepth = 0f;
            vp.MaxDepth = 1f;
            vp.X = 0;
            vp.Y = 0;
            d3dDevice.ImmediateContext.Rasterizer.SetViewport(vp);

            var vertexShaderByteCode = ShaderBytecode.CompileFromFile("../../../ad.fx", "VS", "vs_4_0", ShaderFlags.Debug | ShaderFlags.SkipOptimization | ShaderFlags.EnableStrictness);
            vertexShader = new VertexShader(d3dDevice, vertexShaderByteCode);

            var pixelShaderByteCode = ShaderBytecode.CompileFromFile("../../../ad.fx", "PS", "ps_4_0", ShaderFlags.Debug | ShaderFlags.SkipOptimization | ShaderFlags.EnableStrictness);
            pixelShader = new PixelShader(d3dDevice, pixelShaderByteCode);

            InputElement[] inputElements =
            {
                new InputElement()
                {
                    SemanticName = "POSITION",
                    SemanticIndex = 0,
                    Format = Format.R32G32B32_Float,
                    Slot = 0,
                    AlignedByteOffset = 0,
                    Classification  = InputClassification.PerVertexData,
                    InstanceDataStepRate = 0,
                },
                new InputElement()
                {
                    SemanticName = "TEXCOORD",
                    SemanticIndex = 0,
                    Format = Format.R32G32_Float,
                    Slot = 0,
                    AlignedByteOffset = 12,
                    Classification  = InputClassification.PerVertexData,
                    InstanceDataStepRate = 0,
                }
            };
            ShaderSignature signature = ShaderSignature.GetInputSignature(vertexShaderByteCode);
            InputLayout layout = new InputLayout(d3dDevice, signature, inputElements);

            d3dDevice.ImmediateContext.InputAssembler.InputLayout = layout;
            vertexShaderByteCode.Dispose();
            pixelShaderByteCode.Dispose();

            float[] vertices =
            {
                -1.0f, 1.0f, -1.0f ,  0.0f, 0.0f  ,
                1.0f, 1.0f, -1.0f ,  1.0f, 0.0f  ,
                1.0f, 1.0f, 1.0f ,  1.0f, 1.0f  ,
                -1.0f, 1.0f, 1.0f ,  0.0f, 1.0f  ,

                -1.0f, -1.0f, -1.0f ,  0.0f, 0.0f  ,
                1.0f, -1.0f, -1.0f ,  1.0f, 0.0f  ,
                1.0f, -1.0f, 1.0f ,  1.0f, 1.0f  ,
                -1.0f, -1.0f, 1.0f ,  0.0f, 1.0f  ,

                -1.0f, -1.0f, 1.0f ,  0.0f, 0.0f  ,
                -1.0f, -1.0f, -1.0f ,  1.0f, 0.0f  ,
                -1.0f, 1.0f, -1.0f ,  1.0f, 1.0f  ,
                -1.0f, 1.0f, 1.0f ,  0.0f, 1.0f  ,

                1.0f, -1.0f, 1.0f ,  0.0f, 0.0f  ,
                1.0f, -1.0f, -1.0f ,  1.0f, 0.0f  ,
                1.0f, 1.0f, -1.0f ,  1.0f, 1.0f  ,
                1.0f, 1.0f, 1.0f ,  0.0f, 1.0f  ,

                -1.0f, -1.0f, -1.0f ,  0.0f, 0.0f  ,
                1.0f, -1.0f, -1.0f ,  1.0f, 0.0f  ,
                1.0f, 1.0f, -1.0f ,  1.0f, 1.0f  ,
                -1.0f, 1.0f, -1.0f ,  0.0f, 1.0f  ,

                -1.0f, -1.0f, 1.0f ,  0.0f, 0.0f  ,
                1.0f, -1.0f, 1.0f ,  1.0f, 0.0f  ,
                1.0f, 1.0f, 1.0f ,  1.0f, 1.0f  ,
                -1.0f, 1.0f, 1.0f ,  0.0f, 1.0f  ,
            };

            BufferDescription bd = new BufferDescription();
            bd.Usage = ResourceUsage.Default;
            bd.SizeInBytes = sizeof(float) * vertices.Length;
            bd.BindFlags = BindFlags.VertexBuffer;
            bd.CpuAccessFlags = 0;

            vertexBuffer = Buffer.Create<float>(d3dDevice, vertices, bd);
            VertexBufferBinding vbBind = new VertexBufferBinding(vertexBuffer, sizeof(float) * 5, 0);

            d3dDevice.ImmediateContext.InputAssembler.SetVertexBuffers(0, vbBind);

            UInt16[] indices =
            {
                3,1,0,
                2,1,3,

                6,4,5,
                7,4,6,

                11,9,8,
                10,9,11,

                14,12,13,
                15,12,14,

                19,17,16,
                18,17,19,

                22,20,21,
                23,20,22
            };

            bd.Usage = ResourceUsage.Default;
            bd.SizeInBytes = sizeof(UInt16) * indices.Length;
            bd.BindFlags = BindFlags.IndexBuffer;
            bd.CpuAccessFlags = 0;

            indexBuffer = Buffer.Create<UInt16>(d3dDevice, indices, bd);

            d3dDevice.ImmediateContext.InputAssembler.SetIndexBuffer(indexBuffer, Format.R16_UInt, 0);
            d3dDevice.ImmediateContext.InputAssembler.PrimitiveTopology = PrimitiveTopology.TriangleList;


            bd.Usage = ResourceUsage.Default;
            bd.SizeInBytes = Utilities.SizeOf<Matrix>();
            bd.BindFlags = BindFlags.ConstantBuffer;
            bd.CpuAccessFlags = 0;
            viewMatBuffer = new Buffer(d3dDevice, bd);

            bd.SizeInBytes = Utilities.SizeOf<Matrix>();
            projMatBuffer = new Buffer(d3dDevice, bd);

            rotMatBuffer = new Buffer(d3dDevice, bd);


            textureRV = GetShaderResourceFromFile(d3dDevice, "desktop.png");
            SamplerStateDescription sampDesc = new SamplerStateDescription();
            sampDesc.Filter = Filter.MinMagMipLinear;
            sampDesc.AddressU = TextureAddressMode.Wrap;
            sampDesc.AddressV = TextureAddressMode.Wrap;
            sampDesc.AddressW = TextureAddressMode.Wrap;
            sampDesc.ComparisonFunction = Comparison.Never;
            sampDesc.MinimumLod = 0;
            sampDesc.MaximumLod = float.MaxValue;

            samplerLinear = new SamplerState(d3dDevice, sampDesc);

            viewMat = Matrix.LookAtLH(new Vector3(0.0f, 3.0f, -6.0f), new Vector3(0.0f, 1.0f, 0.0f), new Vector3(0.0f, 1.0f, 0.0f));
            viewMat.Transpose();
            d3dDevice.ImmediateContext.UpdateSubresource(ref viewMat, viewMatBuffer);

            projMat = Matrix.PerspectiveFovLH(0.785398163f, 1.0f, 0.01f, 100.0f);
            projMat.Transpose();
            d3dDevice.ImmediateContext.UpdateSubresource(ref projMat, projMatBuffer);

            rotMat = Matrix.Identity;
            d3dDevice.ImmediateContext.UpdateSubresource(ref rotMat, rotMatBuffer);

        }

        protected override void OnPaint(PaintEventArgs e)
        {

            d3dDevice.ImmediateContext.ClearRenderTargetView(renderTargetView, new SharpDX.Mathematics.Interop.RawColor4(0.0f, 0.125f, 0.3f, 1.0f));
            d3dDevice.ImmediateContext.ClearDepthStencilView(depthStencilView, DepthStencilClearFlags.Depth, 1.0f, 0);

            d3dDevice.ImmediateContext.VertexShader.Set(vertexShader);
            d3dDevice.ImmediateContext.VertexShader.SetConstantBuffer(0, viewMatBuffer);
            d3dDevice.ImmediateContext.VertexShader.SetConstantBuffer(1, projMatBuffer);
            d3dDevice.ImmediateContext.VertexShader.SetConstantBuffer(2, rotMatBuffer);
            d3dDevice.ImmediateContext.PixelShader.Set(pixelShader);
            d3dDevice.ImmediateContext.PixelShader.SetConstantBuffer(0, viewMatBuffer);
            d3dDevice.ImmediateContext.PixelShader.SetShaderResource(0, textureRV);
            d3dDevice.ImmediateContext.PixelShader.SetSampler(0, samplerLinear);
            d3dDevice.ImmediateContext.DrawIndexed(36, 0, 0);

            swapChain.Present(0, 0);

            base.OnPaint(e);
        }

        protected override void OnPaintBackground(PaintEventArgs e)
        {
            //base.OnPaintBackground(e);
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            this.Invalidate();
            base.OnMouseDown(e);
        }

        private static SharpDX.WIC.BitmapSource LoadBitmap(SharpDX.WIC.ImagingFactory2 factory, string filename)
        {
            using (var oBitmapDecoder = new SharpDX.WIC.BitmapDecoder(
                factory,
                filename,
                SharpDX.WIC.DecodeOptions.CacheOnDemand
                ))
            {
                var oFormatConverter = new SharpDX.WIC.FormatConverter(factory);

                oFormatConverter.Initialize(
                    oBitmapDecoder.GetFrame(0),
                    SharpDX.WIC.PixelFormat.Format32bppPRGBA,
                    SharpDX.WIC.BitmapDitherType.None,
                    null,
                    0.0,
                    SharpDX.WIC.BitmapPaletteType.Custom);

                return oFormatConverter;
            }
        }

        private static SharpDX.Direct3D11.Texture2D CreateTexture2DFromBitmap(SharpDX.Direct3D11.Device device, SharpDX.DataStream buffer, int width, int height)
        {
            int iStride = width * 4;
            return new SharpDX.Direct3D11.Texture2D(device, new SharpDX.Direct3D11.Texture2DDescription()
            {
                Width = width,
                Height = height,
                ArraySize = 1,
                BindFlags = SharpDX.Direct3D11.BindFlags.ShaderResource,
                Usage = SharpDX.Direct3D11.ResourceUsage.Immutable,
                CpuAccessFlags = SharpDX.Direct3D11.CpuAccessFlags.None,
                Format = SharpDX.DXGI.Format.R8G8B8A8_UNorm,
                MipLevels = 1,
                OptionFlags = SharpDX.Direct3D11.ResourceOptionFlags.None,
                SampleDescription = new SharpDX.DXGI.SampleDescription(1, 0),
            }, new SharpDX.DataRectangle(buffer.DataPointer, iStride));
        }

        internal ShaderResourceView GetShaderResourceFromFile(SharpDX.Direct3D11.Device device, string imagePath)
        {
            using (var oBitmapSource = LoadBitmap(new SharpDX.WIC.ImagingFactory2(), imagePath))
            {
                //The stride is the number of bytes per "line". This is the width times the number of bytes per pixel, which is 4
                int iStride = oBitmapSource.Size.Width * 4;
                using (var oBuffer = new SharpDX.DataStream(oBitmapSource.Size.Height * iStride, true, true))
                {
                    // Copy the content of the WIC to the buffer
                    oBitmapSource.CopyPixels(iStride, oBuffer);

                    using (var oTexture = CreateTexture2DFromBitmap(device, oBuffer, oBitmapSource.Size.Width, oBitmapSource.Size.Height))
                    {
                        ShaderResourceView oShaderResourceView = new ShaderResourceView(device, oTexture);
                        return oShaderResourceView;
                    }
                }
            }
        }

        struct RotColor
        {
            public Matrix rot;
            public Color4 color;
        }
    }

}

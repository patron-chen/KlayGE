// RenderLayout.hpp
// KlayGE 渲染流布局类 头文件
// Ver 3.6.0
// 版权所有(C) 龚敏敏, 2006-2007
// Homepage: http://klayge.sourceforge.net
//
// 3.6.0
// 去掉了TT_TriangleFan (2007.6.23)
//
// 3.2.0
// 初次建立 (2006.1.9)
//
// 修改记录
/////////////////////////////////////////////////////////////////////////////////

#ifndef _RENDERLAYOUT_HPP
#define _RENDERLAYOUT_HPP

#ifndef KLAYGE_CORE_SOURCE
#define KLAYGE_LIB_NAME KlayGE_Core
#include <KlayGE/config/auto_link.hpp>
#endif

#include <KlayGE/PreDeclare.hpp>

#include <vector>
#include <boost/utility.hpp>
#include <boost/tuple/tuple.hpp>

#include <KlayGE/GraphicsBuffer.hpp>
#include <KlayGE/ElementFormat.hpp>

namespace KlayGE
{
	enum VertexElementUsage
	{
		// vertex positions
		VEU_Position,
		// vertex normals included (for lighting)
		VEU_Normal,
		// Vertex colors - diffuse
		VEU_Diffuse,
		// Vertex colors - specular
		VEU_Specular,
		// Vertex blend weights
		VEU_BlendWeight,
		// Vertex blend indices
		VEU_BlendIndex,
		// at least one set of texture coords (exact number specified in class)
		VEU_TextureCoord,
		// Vertex tangent
		VEU_Tangent,
		// Vertex binormal
		VEU_Binormal
	};

	struct vertex_element
	{
		vertex_element()
		{
		}
		vertex_element(VertexElementUsage usage, uint8_t usage_index, ElementFormat format)
			: usage(usage), usage_index(usage_index), format(format)
		{
		}

		VertexElementUsage usage;
		uint8_t usage_index;

		ElementFormat format;

		uint16_t element_size() const
		{
			return NumFormatBytes(format);
		}

		friend bool
		operator==(vertex_element const & lhs, vertex_element const & rhs)
		{
			return (lhs.usage == rhs.usage)
				&& (lhs.usage_index == rhs.usage_index)
				&& (lhs.format == rhs.format);
		}
	};
	typedef std::vector<vertex_element> vertex_elements_type;


	class KLAYGE_CORE_API RenderLayout
	{
	public:
		enum topology_type
		{
			TT_PointList,
			TT_LineList,
			TT_LineStrip,
			TT_TriangleList,
			TT_TriangleStrip
		};

		enum stream_type
		{
			ST_Geometry,
			ST_Instance
		};

		RenderLayout();
		virtual ~RenderLayout() = 0;

		static RenderLayoutPtr NullObject();

		void TopologyType(topology_type type)
		{
			topo_type_ = type;
		}
		topology_type TopologyType() const
		{
			return topo_type_;
		}

		uint32_t NumVertices() const;

		template <typename tuple_type>
		void BindVertexStream(GraphicsBufferPtr buffer, tuple_type const & vertex_elems,
			stream_type type = ST_Geometry, uint32_t freq = 1)
		{
			this->BindVertexStream(buffer, Tuple2Vector(vertex_elems), type, freq);
		}
		void BindVertexStream(GraphicsBufferPtr buffer, vertex_elements_type const & vet,
			stream_type type = ST_Geometry, uint32_t freq = 1);

		uint32_t NumVertexStreams() const
		{
			return static_cast<uint32_t>(vertex_streams_.size());
		}
		GraphicsBufferPtr const & GetVertexStream(uint32_t index) const
		{
			return vertex_streams_[index].stream;
		}
		vertex_elements_type const & VertexStreamFormat(uint32_t index) const
		{
			return vertex_streams_[index].format;
		}
		uint32_t VertexSize(uint32_t index) const
		{
			return vertex_streams_[index].vertex_size;
		}
		stream_type VertexStreamType(uint32_t index) const
		{
			return vertex_streams_[index].type;
		}
		uint32_t VertexStreamFrequency(uint32_t index) const
		{
			return vertex_streams_[index].freq;
		}
		void VertexStreamFrequencyDivider(uint32_t index, stream_type type, uint32_t freq)
		{
			vertex_streams_[index].type = type;
			vertex_streams_[index].freq = freq;
		}

		bool UseIndices() const;
		uint32_t NumIndices() const;

		void BindIndexStream(GraphicsBufferPtr index_stream, ElementFormat format);
		GraphicsBufferPtr const & GetIndexStream() const;
		ElementFormat IndexStreamFormat() const
		{
			return index_format_;
		}

		GraphicsBufferPtr const & InstanceStream() const;
		vertex_elements_type const & InstanceStreamFormat() const
		{
			return instance_stream_.format;
		}
		uint32_t InstanceSize() const
		{
			return instance_stream_.vertex_size;
		}
		uint32_t NumInstance() const;

		void ExpandInstance(GraphicsBufferPtr& hint, uint32_t inst_no) const;

	private:
		template <typename tuple_type>
		vertex_elements_type Tuple2Vector(tuple_type const & t)
		{
			vertex_elements_type ret;
			ret.push_back(boost::tuples::get<0>(t));

			vertex_elements_type tail(Tuple2Vector(t.get_tail()));
			ret.insert(ret.end(), tail.begin(), tail.end());

			return ret;
		}

	protected:
		topology_type topo_type_;

		struct StreamUnit
		{
			GraphicsBufferPtr stream;
			vertex_elements_type format;
			uint32_t vertex_size;

			stream_type type;
			uint32_t freq;
		};

		std::vector<StreamUnit> vertex_streams_;
		StreamUnit instance_stream_;

		GraphicsBufferPtr index_stream_;
		ElementFormat index_format_;
	};

	template <>
	inline vertex_elements_type
	RenderLayout::Tuple2Vector<boost::tuples::null_type>(boost::tuples::null_type const & /*t*/)
	{
		return vertex_elements_type();
	}
}

#endif		// _RENDERLAYOUT_HPP

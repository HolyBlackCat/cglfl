/*
  OpenGL Function Loader (GLFL) v1.0.1
  Copyright (C) 2017 Egor Mikhailov <blckcat@inbox.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "GLFL/glfl.h"
#include "GLFL/glfl_func_indices.h"


glfl::context *glfl::current_context = 0, *glfl::default_context = 0;

void glfl::set_active_context(context *c)
{
    if (c == 0)
    {
        if (default_context == 0)
            default_context = new context;
        current_context = default_context;
    }
    else
        current_context = c;
}

void glfl::set_function_loader(function_loader_t ptr)
{
    if (current_context == 0)
        current_context = default_context = new context;
    current_context->function_loader = ptr;
    current_context->ptrs[0] = current_context->function_loader("meow");
}

void glfl::load_all_versions()
{
    load_gl();
    load_gles();
    load_glsc();
}

void glfl::load_everything()
{
    load_all_versions();
    load_extension_GL_3DFX_multisample();
    load_extension_GL_3DFX_tbuffer();
    load_extension_GL_3DFX_texture_compression_FXT1();
    load_extension_GL_AMD_blend_minmax_factor();
    load_extension_GL_AMD_compressed_3DC_texture();
    load_extension_GL_AMD_compressed_ATC_texture();
    load_extension_GL_AMD_conservative_depth();
    load_extension_GL_AMD_debug_output();
    load_extension_GL_AMD_depth_clamp_separate();
    load_extension_GL_AMD_draw_buffers_blend();
    load_extension_GL_AMD_framebuffer_sample_positions();
    load_extension_GL_AMD_gcn_shader();
    load_extension_GL_AMD_gpu_shader_half_float();
    load_extension_GL_AMD_gpu_shader_int64();
    load_extension_GL_AMD_interleaved_elements();
    load_extension_GL_AMD_multi_draw_indirect();
    load_extension_GL_AMD_name_gen_delete();
    load_extension_GL_AMD_occlusion_query_event();
    load_extension_GL_AMD_performance_monitor();
    load_extension_GL_AMD_pinned_memory();
    load_extension_GL_AMD_program_binary_Z400();
    load_extension_GL_AMD_query_buffer_object();
    load_extension_GL_AMD_sample_positions();
    load_extension_GL_AMD_seamless_cubemap_per_texture();
    load_extension_GL_AMD_shader_atomic_counter_ops();
    load_extension_GL_AMD_shader_ballot();
    load_extension_GL_AMD_shader_stencil_export();
    load_extension_GL_AMD_shader_trinary_minmax();
    load_extension_GL_AMD_shader_explicit_vertex_parameter();
    load_extension_GL_AMD_sparse_texture();
    load_extension_GL_AMD_stencil_operation_extended();
    load_extension_GL_AMD_texture_texture4();
    load_extension_GL_AMD_transform_feedback3_lines_triangles();
    load_extension_GL_AMD_transform_feedback4();
    load_extension_GL_AMD_vertex_shader_layer();
    load_extension_GL_AMD_vertex_shader_tessellator();
    load_extension_GL_AMD_vertex_shader_viewport_index();
    load_extension_GL_ANDROID_extension_pack_es31a();
    load_extension_GL_ANGLE_depth_texture();
    load_extension_GL_ANGLE_framebuffer_blit();
    load_extension_GL_ANGLE_framebuffer_multisample();
    load_extension_GL_ANGLE_instanced_arrays();
    load_extension_GL_ANGLE_pack_reverse_row_order();
    load_extension_GL_ANGLE_program_binary();
    load_extension_GL_ANGLE_texture_compression_dxt3();
    load_extension_GL_ANGLE_texture_compression_dxt5();
    load_extension_GL_ANGLE_texture_usage();
    load_extension_GL_ANGLE_translated_shader_source();
    load_extension_GL_APPLE_aux_depth_stencil();
    load_extension_GL_APPLE_client_storage();
    load_extension_GL_APPLE_clip_distance();
    load_extension_GL_APPLE_color_buffer_packed_float();
    load_extension_GL_APPLE_copy_texture_levels();
    load_extension_GL_APPLE_element_array();
    load_extension_GL_APPLE_fence();
    load_extension_GL_APPLE_float_pixels();
    load_extension_GL_APPLE_flush_buffer_range();
    load_extension_GL_APPLE_framebuffer_multisample();
    load_extension_GL_APPLE_object_purgeable();
    load_extension_GL_APPLE_rgb_422();
    load_extension_GL_APPLE_row_bytes();
    load_extension_GL_APPLE_specular_vector();
    load_extension_GL_APPLE_sync();
    load_extension_GL_APPLE_texture_2D_limited_npot();
    load_extension_GL_APPLE_texture_format_BGRA8888();
    load_extension_GL_APPLE_texture_max_level();
    load_extension_GL_APPLE_texture_packed_float();
    load_extension_GL_APPLE_texture_range();
    load_extension_GL_APPLE_transform_hint();
    load_extension_GL_APPLE_vertex_array_object();
    load_extension_GL_APPLE_vertex_array_range();
    load_extension_GL_APPLE_vertex_program_evaluators();
    load_extension_GL_APPLE_ycbcr_422();
    load_extension_GL_ARB_ES2_compatibility();
    load_extension_GL_ARB_ES3_1_compatibility();
    load_extension_GL_ARB_ES3_2_compatibility();
    load_extension_GL_ARB_ES3_compatibility();
    load_extension_GL_ARB_arrays_of_arrays();
    load_extension_GL_ARB_base_instance();
    load_extension_GL_ARB_bindless_texture();
    load_extension_GL_ARB_blend_func_extended();
    load_extension_GL_ARB_buffer_storage();
    load_extension_GL_ARB_cl_event();
    load_extension_GL_ARB_clear_buffer_object();
    load_extension_GL_ARB_clear_texture();
    load_extension_GL_ARB_clip_control();
    load_extension_GL_ARB_color_buffer_float();
    load_extension_GL_ARB_compatibility();
    load_extension_GL_ARB_compressed_texture_pixel_storage();
    load_extension_GL_ARB_compute_shader();
    load_extension_GL_ARB_compute_variable_group_size();
    load_extension_GL_ARB_conditional_render_inverted();
    load_extension_GL_ARB_conservative_depth();
    load_extension_GL_ARB_copy_buffer();
    load_extension_GL_ARB_copy_image();
    load_extension_GL_ARB_cull_distance();
    load_extension_GL_ARB_debug_output();
    load_extension_GL_ARB_depth_buffer_float();
    load_extension_GL_ARB_depth_clamp();
    load_extension_GL_ARB_depth_texture();
    load_extension_GL_ARB_derivative_control();
    load_extension_GL_ARB_direct_state_access();
    load_extension_GL_ARB_draw_buffers();
    load_extension_GL_ARB_draw_buffers_blend();
    load_extension_GL_ARB_draw_elements_base_vertex();
    load_extension_GL_ARB_draw_indirect();
    load_extension_GL_ARB_draw_instanced();
    load_extension_GL_ARB_enhanced_layouts();
    load_extension_GL_ARB_explicit_attrib_location();
    load_extension_GL_ARB_explicit_uniform_location();
    load_extension_GL_ARB_fragment_coord_conventions();
    load_extension_GL_ARB_fragment_layer_viewport();
    load_extension_GL_ARB_fragment_program();
    load_extension_GL_ARB_fragment_program_shadow();
    load_extension_GL_ARB_fragment_shader();
    load_extension_GL_ARB_fragment_shader_interlock();
    load_extension_GL_ARB_framebuffer_no_attachments();
    load_extension_GL_ARB_framebuffer_object();
    load_extension_GL_ARB_framebuffer_sRGB();
    load_extension_GL_ARB_geometry_shader4();
    load_extension_GL_ARB_get_program_binary();
    load_extension_GL_ARB_get_texture_sub_image();
    load_extension_GL_ARB_gpu_shader5();
    load_extension_GL_ARB_gpu_shader_fp64();
    load_extension_GL_ARB_gpu_shader_int64();
    load_extension_GL_ARB_half_float_pixel();
    load_extension_GL_ARB_half_float_vertex();
    load_extension_GL_ARB_imaging();
    load_extension_GL_ARB_indirect_parameters();
    load_extension_GL_ARB_instanced_arrays();
    load_extension_GL_ARB_internalformat_query();
    load_extension_GL_ARB_internalformat_query2();
    load_extension_GL_ARB_invalidate_subdata();
    load_extension_GL_ARB_map_buffer_alignment();
    load_extension_GL_ARB_map_buffer_range();
    load_extension_GL_ARB_matrix_palette();
    load_extension_GL_ARB_multi_bind();
    load_extension_GL_ARB_multi_draw_indirect();
    load_extension_GL_ARB_multisample();
    load_extension_GL_ARB_multitexture();
    load_extension_GL_ARB_occlusion_query();
    load_extension_GL_ARB_occlusion_query2();
    load_extension_GL_ARB_parallel_shader_compile();
    load_extension_GL_ARB_pipeline_statistics_query();
    load_extension_GL_ARB_pixel_buffer_object();
    load_extension_GL_ARB_point_parameters();
    load_extension_GL_ARB_point_sprite();
    load_extension_GL_ARB_post_depth_coverage();
    load_extension_GL_ARB_program_interface_query();
    load_extension_GL_ARB_provoking_vertex();
    load_extension_GL_ARB_query_buffer_object();
    load_extension_GL_ARB_robust_buffer_access_behavior();
    load_extension_GL_ARB_robustness();
    load_extension_GL_ARB_robustness_isolation();
    load_extension_GL_ARB_sample_locations();
    load_extension_GL_ARB_sample_shading();
    load_extension_GL_ARB_sampler_objects();
    load_extension_GL_ARB_seamless_cube_map();
    load_extension_GL_ARB_seamless_cubemap_per_texture();
    load_extension_GL_ARB_separate_shader_objects();
    load_extension_GL_ARB_shader_atomic_counter_ops();
    load_extension_GL_ARB_shader_atomic_counters();
    load_extension_GL_ARB_shader_ballot();
    load_extension_GL_ARB_shader_bit_encoding();
    load_extension_GL_ARB_shader_clock();
    load_extension_GL_ARB_shader_draw_parameters();
    load_extension_GL_ARB_shader_group_vote();
    load_extension_GL_ARB_shader_image_load_store();
    load_extension_GL_ARB_shader_image_size();
    load_extension_GL_ARB_shader_objects();
    load_extension_GL_ARB_shader_precision();
    load_extension_GL_ARB_shader_stencil_export();
    load_extension_GL_ARB_shader_storage_buffer_object();
    load_extension_GL_ARB_shader_subroutine();
    load_extension_GL_ARB_shader_texture_image_samples();
    load_extension_GL_ARB_shader_texture_lod();
    load_extension_GL_ARB_shader_viewport_layer_array();
    load_extension_GL_ARB_shading_language_100();
    load_extension_GL_ARB_shading_language_420pack();
    load_extension_GL_ARB_shading_language_include();
    load_extension_GL_ARB_shading_language_packing();
    load_extension_GL_ARB_shadow();
    load_extension_GL_ARB_shadow_ambient();
    load_extension_GL_ARB_sparse_buffer();
    load_extension_GL_ARB_sparse_texture();
    load_extension_GL_ARB_sparse_texture2();
    load_extension_GL_ARB_sparse_texture_clamp();
    load_extension_GL_ARB_stencil_texturing();
    load_extension_GL_ARB_sync();
    load_extension_GL_ARB_tessellation_shader();
    load_extension_GL_ARB_texture_barrier();
    load_extension_GL_ARB_texture_border_clamp();
    load_extension_GL_ARB_texture_buffer_object();
    load_extension_GL_ARB_texture_buffer_object_rgb32();
    load_extension_GL_ARB_texture_buffer_range();
    load_extension_GL_ARB_texture_compression();
    load_extension_GL_ARB_texture_compression_bptc();
    load_extension_GL_ARB_texture_compression_rgtc();
    load_extension_GL_ARB_texture_cube_map();
    load_extension_GL_ARB_texture_cube_map_array();
    load_extension_GL_ARB_texture_env_add();
    load_extension_GL_ARB_texture_env_combine();
    load_extension_GL_ARB_texture_env_crossbar();
    load_extension_GL_ARB_texture_env_dot3();
    load_extension_GL_ARB_texture_filter_minmax();
    load_extension_GL_ARB_texture_float();
    load_extension_GL_ARB_texture_gather();
    load_extension_GL_ARB_texture_mirror_clamp_to_edge();
    load_extension_GL_ARB_texture_mirrored_repeat();
    load_extension_GL_ARB_texture_multisample();
    load_extension_GL_ARB_texture_non_power_of_two();
    load_extension_GL_ARB_texture_query_levels();
    load_extension_GL_ARB_texture_query_lod();
    load_extension_GL_ARB_texture_rectangle();
    load_extension_GL_ARB_texture_rg();
    load_extension_GL_ARB_texture_rgb10_a2ui();
    load_extension_GL_ARB_texture_stencil8();
    load_extension_GL_ARB_texture_storage();
    load_extension_GL_ARB_texture_storage_multisample();
    load_extension_GL_ARB_texture_swizzle();
    load_extension_GL_ARB_texture_view();
    load_extension_GL_ARB_timer_query();
    load_extension_GL_ARB_transform_feedback2();
    load_extension_GL_ARB_transform_feedback3();
    load_extension_GL_ARB_transform_feedback_instanced();
    load_extension_GL_ARB_transform_feedback_overflow_query();
    load_extension_GL_ARB_transpose_matrix();
    load_extension_GL_ARB_uniform_buffer_object();
    load_extension_GL_ARB_vertex_array_bgra();
    load_extension_GL_ARB_vertex_array_object();
    load_extension_GL_ARB_vertex_attrib_64bit();
    load_extension_GL_ARB_vertex_attrib_binding();
    load_extension_GL_ARB_vertex_blend();
    load_extension_GL_ARB_vertex_buffer_object();
    load_extension_GL_ARB_vertex_program();
    load_extension_GL_ARB_vertex_shader();
    load_extension_GL_ARB_vertex_type_10f_11f_11f_rev();
    load_extension_GL_ARB_vertex_type_2_10_10_10_rev();
    load_extension_GL_ARB_viewport_array();
    load_extension_GL_ARB_window_pos();
    load_extension_GL_ARM_mali_program_binary();
    load_extension_GL_ARM_mali_shader_binary();
    load_extension_GL_ARM_rgba8();
    load_extension_GL_ARM_shader_framebuffer_fetch();
    load_extension_GL_ARM_shader_framebuffer_fetch_depth_stencil();
    load_extension_GL_ATI_draw_buffers();
    load_extension_GL_ATI_element_array();
    load_extension_GL_ATI_envmap_bumpmap();
    load_extension_GL_ATI_fragment_shader();
    load_extension_GL_ATI_map_object_buffer();
    load_extension_GL_ATI_meminfo();
    load_extension_GL_ATI_pixel_format_float();
    load_extension_GL_ATI_pn_triangles();
    load_extension_GL_ATI_separate_stencil();
    load_extension_GL_ATI_text_fragment_shader();
    load_extension_GL_ATI_texture_env_combine3();
    load_extension_GL_ATI_texture_float();
    load_extension_GL_ATI_texture_mirror_once();
    load_extension_GL_ATI_vertex_array_object();
    load_extension_GL_ATI_vertex_attrib_array_object();
    load_extension_GL_ATI_vertex_streams();
    load_extension_GL_DMP_program_binary();
    load_extension_GL_DMP_shader_binary();
    load_extension_GL_EXT_422_pixels();
    load_extension_GL_EXT_YUV_target();
    load_extension_GL_EXT_abgr();
    load_extension_GL_EXT_base_instance();
    load_extension_GL_EXT_bgra();
    load_extension_GL_EXT_bindable_uniform();
    load_extension_GL_EXT_blend_color();
    load_extension_GL_EXT_blend_equation_separate();
    load_extension_GL_EXT_blend_func_extended();
    load_extension_GL_EXT_blend_func_separate();
    load_extension_GL_EXT_blend_logic_op();
    load_extension_GL_EXT_blend_minmax();
    load_extension_GL_EXT_blend_subtract();
    load_extension_GL_EXT_buffer_storage();
    load_extension_GL_EXT_clear_texture();
    load_extension_GL_EXT_clip_cull_distance();
    load_extension_GL_EXT_clip_volume_hint();
    load_extension_GL_EXT_cmyka();
    load_extension_GL_EXT_color_buffer_float();
    load_extension_GL_EXT_color_buffer_half_float();
    load_extension_GL_EXT_color_subtable();
    load_extension_GL_EXT_compiled_vertex_array();
    load_extension_GL_EXT_conservative_depth();
    load_extension_GL_EXT_convolution();
    load_extension_GL_EXT_coordinate_frame();
    load_extension_GL_EXT_copy_image();
    load_extension_GL_EXT_copy_texture();
    load_extension_GL_EXT_cull_vertex();
    load_extension_GL_EXT_debug_label();
    load_extension_GL_EXT_debug_marker();
    load_extension_GL_EXT_depth_bounds_test();
    load_extension_GL_EXT_direct_state_access();
    load_extension_GL_EXT_discard_framebuffer();
    load_extension_GL_EXT_disjoint_timer_query();
    load_extension_GL_EXT_draw_buffers();
    load_extension_GL_EXT_draw_buffers2();
    load_extension_GL_EXT_draw_buffers_indexed();
    load_extension_GL_EXT_draw_elements_base_vertex();
    load_extension_GL_EXT_draw_instanced();
    load_extension_GL_EXT_draw_range_elements();
    load_extension_GL_EXT_draw_transform_feedback();
    load_extension_GL_EXT_float_blend();
    load_extension_GL_EXT_fog_coord();
    load_extension_GL_EXT_framebuffer_blit();
    load_extension_GL_EXT_framebuffer_multisample();
    load_extension_GL_EXT_framebuffer_multisample_blit_scaled();
    load_extension_GL_EXT_framebuffer_object();
    load_extension_GL_EXT_framebuffer_sRGB();
    load_extension_GL_EXT_geometry_point_size();
    load_extension_GL_EXT_geometry_shader();
    load_extension_GL_EXT_geometry_shader4();
    load_extension_GL_EXT_gpu_program_parameters();
    load_extension_GL_EXT_gpu_shader4();
    load_extension_GL_EXT_gpu_shader5();
    load_extension_GL_EXT_histogram();
    load_extension_GL_EXT_index_array_formats();
    load_extension_GL_EXT_index_func();
    load_extension_GL_EXT_index_material();
    load_extension_GL_EXT_index_texture();
    load_extension_GL_EXT_instanced_arrays();
    load_extension_GL_EXT_light_texture();
    load_extension_GL_EXT_map_buffer_range();
    load_extension_GL_EXT_misc_attribute();
    load_extension_GL_EXT_multi_draw_arrays();
    load_extension_GL_EXT_multi_draw_indirect();
    load_extension_GL_EXT_multisample();
    load_extension_GL_EXT_multisampled_compatibility();
    load_extension_GL_EXT_multisampled_render_to_texture();
    load_extension_GL_EXT_multiview_draw_buffers();
    load_extension_GL_EXT_occlusion_query_boolean();
    load_extension_GL_EXT_packed_depth_stencil();
    load_extension_GL_EXT_packed_float();
    load_extension_GL_EXT_packed_pixels();
    load_extension_GL_EXT_paletted_texture();
    load_extension_GL_EXT_pixel_buffer_object();
    load_extension_GL_EXT_pixel_transform();
    load_extension_GL_EXT_pixel_transform_color_table();
    load_extension_GL_EXT_point_parameters();
    load_extension_GL_EXT_polygon_offset();
    load_extension_GL_EXT_polygon_offset_clamp();
    load_extension_GL_EXT_post_depth_coverage();
    load_extension_GL_EXT_primitive_bounding_box();
    load_extension_GL_EXT_protected_textures();
    load_extension_GL_EXT_provoking_vertex();
    load_extension_GL_EXT_pvrtc_sRGB();
    load_extension_GL_EXT_raster_multisample();
    load_extension_GL_EXT_read_format_bgra();
    load_extension_GL_EXT_render_snorm();
    load_extension_GL_EXT_rescale_normal();
    load_extension_GL_EXT_robustness();
    load_extension_GL_EXT_sRGB();
    load_extension_GL_EXT_sRGB_write_control();
    load_extension_GL_EXT_secondary_color();
    load_extension_GL_EXT_separate_shader_objects();
    load_extension_GL_EXT_separate_specular_color();
    load_extension_GL_EXT_shader_framebuffer_fetch();
    load_extension_GL_EXT_shader_group_vote();
    load_extension_GL_EXT_shader_image_load_formatted();
    load_extension_GL_EXT_shader_image_load_store();
    load_extension_GL_EXT_shader_implicit_conversions();
    load_extension_GL_EXT_shader_integer_mix();
    load_extension_GL_EXT_shader_io_blocks();
    load_extension_GL_EXT_shader_non_constant_global_initializers();
    load_extension_GL_EXT_shader_pixel_local_storage();
    load_extension_GL_EXT_shader_pixel_local_storage2();
    load_extension_GL_EXT_shader_texture_lod();
    load_extension_GL_EXT_shadow_funcs();
    load_extension_GL_EXT_shadow_samplers();
    load_extension_GL_EXT_shared_texture_palette();
    load_extension_GL_EXT_sparse_texture();
    load_extension_GL_EXT_sparse_texture2();
    load_extension_GL_EXT_stencil_clear_tag();
    load_extension_GL_EXT_stencil_two_side();
    load_extension_GL_EXT_stencil_wrap();
    load_extension_GL_EXT_subtexture();
    load_extension_GL_EXT_tessellation_point_size();
    load_extension_GL_EXT_tessellation_shader();
    load_extension_GL_EXT_texture();
    load_extension_GL_EXT_texture3D();
    load_extension_GL_EXT_texture_array();
    load_extension_GL_EXT_texture_border_clamp();
    load_extension_GL_EXT_texture_buffer();
    load_extension_GL_EXT_texture_buffer_object();
    load_extension_GL_EXT_texture_compression_dxt1();
    load_extension_GL_EXT_texture_compression_latc();
    load_extension_GL_EXT_texture_compression_rgtc();
    load_extension_GL_EXT_texture_compression_s3tc();
    load_extension_GL_EXT_texture_cube_map();
    load_extension_GL_EXT_texture_cube_map_array();
    load_extension_GL_EXT_texture_env_add();
    load_extension_GL_EXT_texture_env_combine();
    load_extension_GL_EXT_texture_env_dot3();
    load_extension_GL_EXT_texture_filter_anisotropic();
    load_extension_GL_EXT_texture_filter_minmax();
    load_extension_GL_EXT_texture_format_BGRA8888();
    load_extension_GL_EXT_texture_integer();
    load_extension_GL_EXT_texture_lod_bias();
    load_extension_GL_EXT_texture_mirror_clamp();
    load_extension_GL_EXT_texture_norm16();
    load_extension_GL_EXT_texture_object();
    load_extension_GL_EXT_texture_perturb_normal();
    load_extension_GL_EXT_texture_rg();
    load_extension_GL_EXT_texture_sRGB();
    load_extension_GL_EXT_texture_sRGB_R8();
    load_extension_GL_EXT_texture_sRGB_RG8();
    load_extension_GL_EXT_texture_sRGB_decode();
    load_extension_GL_EXT_texture_shared_exponent();
    load_extension_GL_EXT_texture_snorm();
    load_extension_GL_EXT_texture_storage();
    load_extension_GL_EXT_texture_swizzle();
    load_extension_GL_EXT_texture_type_2_10_10_10_REV();
    load_extension_GL_EXT_texture_view();
    load_extension_GL_EXT_timer_query();
    load_extension_GL_EXT_transform_feedback();
    load_extension_GL_EXT_unpack_subimage();
    load_extension_GL_EXT_vertex_array();
    load_extension_GL_EXT_vertex_array_bgra();
    load_extension_GL_EXT_vertex_attrib_64bit();
    load_extension_GL_EXT_vertex_shader();
    load_extension_GL_EXT_vertex_weighting();
    load_extension_GL_EXT_window_rectangles();
    load_extension_GL_EXT_x11_sync_object();
    load_extension_GL_FJ_shader_binary_GCCSO();
    load_extension_GL_GREMEDY_frame_terminator();
    load_extension_GL_GREMEDY_string_marker();
    load_extension_GL_HP_convolution_border_modes();
    load_extension_GL_HP_image_transform();
    load_extension_GL_HP_occlusion_test();
    load_extension_GL_HP_texture_lighting();
    load_extension_GL_IBM_cull_vertex();
    load_extension_GL_IBM_multimode_draw_arrays();
    load_extension_GL_IBM_rasterpos_clip();
    load_extension_GL_IBM_static_data();
    load_extension_GL_IBM_texture_mirrored_repeat();
    load_extension_GL_IBM_vertex_array_lists();
    load_extension_GL_IMG_bindless_texture();
    load_extension_GL_IMG_framebuffer_downsample();
    load_extension_GL_IMG_multisampled_render_to_texture();
    load_extension_GL_IMG_program_binary();
    load_extension_GL_IMG_read_format();
    load_extension_GL_IMG_shader_binary();
    load_extension_GL_IMG_texture_compression_pvrtc();
    load_extension_GL_IMG_texture_compression_pvrtc2();
    load_extension_GL_IMG_texture_env_enhanced_fixed_function();
    load_extension_GL_IMG_texture_filter_cubic();
    load_extension_GL_IMG_user_clip_plane();
    load_extension_GL_INGR_blend_func_separate();
    load_extension_GL_INGR_color_clamp();
    load_extension_GL_INGR_interlace_read();
    load_extension_GL_INTEL_conservative_rasterization();
    load_extension_GL_INTEL_fragment_shader_ordering();
    load_extension_GL_INTEL_framebuffer_CMAA();
    load_extension_GL_INTEL_map_texture();
    load_extension_GL_INTEL_parallel_arrays();
    load_extension_GL_INTEL_performance_query();
    load_extension_GL_KHR_blend_equation_advanced();
    load_extension_GL_KHR_blend_equation_advanced_coherent();
    load_extension_GL_KHR_context_flush_control();
    load_extension_GL_KHR_debug();
    load_extension_GL_KHR_no_error();
    load_extension_GL_KHR_robust_buffer_access_behavior();
    load_extension_GL_KHR_robustness();
    load_extension_GL_KHR_texture_compression_astc_hdr();
    load_extension_GL_KHR_texture_compression_astc_ldr();
    load_extension_GL_KHR_texture_compression_astc_sliced_3d();
    load_extension_GL_MESAX_texture_stack();
    load_extension_GL_MESA_pack_invert();
    load_extension_GL_MESA_resize_buffers();
    load_extension_GL_MESA_window_pos();
    load_extension_GL_MESA_ycbcr_texture();
    load_extension_GL_NVX_conditional_render();
    load_extension_GL_NVX_gpu_memory_info();
    load_extension_GL_NV_bindless_multi_draw_indirect();
    load_extension_GL_NV_bindless_multi_draw_indirect_count();
    load_extension_GL_NV_bindless_texture();
    load_extension_GL_NV_blend_equation_advanced();
    load_extension_GL_NV_blend_equation_advanced_coherent();
    load_extension_GL_NV_blend_square();
    load_extension_GL_NV_clip_space_w_scaling();
    load_extension_GL_NV_command_list();
    load_extension_GL_NV_compute_program5();
    load_extension_GL_NV_conditional_render();
    load_extension_GL_NV_conservative_raster();
    load_extension_GL_NV_conservative_raster_dilate();
    load_extension_GL_NV_conservative_raster_pre_snap_triangles();
    load_extension_GL_NV_copy_buffer();
    load_extension_GL_NV_copy_depth_to_color();
    load_extension_GL_NV_copy_image();
    load_extension_GL_NV_coverage_sample();
    load_extension_GL_NV_deep_texture3D();
    load_extension_GL_NV_depth_buffer_float();
    load_extension_GL_NV_depth_clamp();
    load_extension_GL_NV_depth_nonlinear();
    load_extension_GL_NV_draw_buffers();
    load_extension_GL_NV_draw_instanced();
    load_extension_GL_NV_draw_texture();
    load_extension_GL_NV_evaluators();
    load_extension_GL_NV_explicit_attrib_location();
    load_extension_GL_NV_explicit_multisample();
    load_extension_GL_NV_fbo_color_attachments();
    load_extension_GL_NV_fence();
    load_extension_GL_NV_fill_rectangle();
    load_extension_GL_NV_float_buffer();
    load_extension_GL_NV_fog_distance();
    load_extension_GL_NV_fragment_coverage_to_color();
    load_extension_GL_NV_fragment_program();
    load_extension_GL_NV_fragment_program2();
    load_extension_GL_NV_fragment_program4();
    load_extension_GL_NV_fragment_program_option();
    load_extension_GL_NV_fragment_shader_interlock();
    load_extension_GL_NV_framebuffer_blit();
    load_extension_GL_NV_framebuffer_mixed_samples();
    load_extension_GL_NV_framebuffer_multisample();
    load_extension_GL_NV_framebuffer_multisample_coverage();
    load_extension_GL_NV_generate_mipmap_sRGB();
    load_extension_GL_NV_geometry_program4();
    load_extension_GL_NV_geometry_shader4();
    load_extension_GL_NV_geometry_shader_passthrough();
    load_extension_GL_NV_gpu_program4();
    load_extension_GL_NV_gpu_program5();
    load_extension_GL_NV_gpu_program5_mem_extended();
    load_extension_GL_NV_gpu_shader5();
    load_extension_GL_NV_half_float();
    load_extension_GL_NV_image_formats();
    load_extension_GL_NV_instanced_arrays();
    load_extension_GL_NV_internalformat_sample_query();
    load_extension_GL_NV_light_max_exponent();
    load_extension_GL_NV_multisample_coverage();
    load_extension_GL_NV_multisample_filter_hint();
    load_extension_GL_NV_non_square_matrices();
    load_extension_GL_NV_occlusion_query();
    load_extension_GL_NV_packed_depth_stencil();
    load_extension_GL_NV_parameter_buffer_object();
    load_extension_GL_NV_parameter_buffer_object2();
    load_extension_GL_NV_path_rendering();
    load_extension_GL_NV_path_rendering_shared_edge();
    load_extension_GL_NV_pixel_data_range();
    load_extension_GL_NV_point_sprite();
    load_extension_GL_NV_polygon_mode();
    load_extension_GL_NV_present_video();
    load_extension_GL_NV_primitive_restart();
    load_extension_GL_NV_read_buffer();
    load_extension_GL_NV_read_buffer_front();
    load_extension_GL_NV_read_depth();
    load_extension_GL_NV_read_depth_stencil();
    load_extension_GL_NV_read_stencil();
    load_extension_GL_NV_register_combiners();
    load_extension_GL_NV_register_combiners2();
    load_extension_GL_NV_robustness_video_memory_purge();
    load_extension_GL_NV_sRGB_formats();
    load_extension_GL_NV_sample_locations();
    load_extension_GL_NV_sample_mask_override_coverage();
    load_extension_GL_NV_shader_atomic_counters();
    load_extension_GL_NV_shader_atomic_float();
    load_extension_GL_NV_shader_atomic_float64();
    load_extension_GL_NV_shader_atomic_fp16_vector();
    load_extension_GL_NV_shader_atomic_int64();
    load_extension_GL_NV_shader_buffer_load();
    load_extension_GL_NV_shader_buffer_store();
    load_extension_GL_NV_shader_noperspective_interpolation();
    load_extension_GL_NV_shader_storage_buffer_object();
    load_extension_GL_NV_shader_thread_group();
    load_extension_GL_NV_shader_thread_shuffle();
    load_extension_GL_NV_shadow_samplers_array();
    load_extension_GL_NV_shadow_samplers_cube();
    load_extension_GL_NV_stereo_view_rendering();
    load_extension_GL_NV_tessellation_program5();
    load_extension_GL_NV_texgen_emboss();
    load_extension_GL_NV_texgen_reflection();
    load_extension_GL_NV_texture_barrier();
    load_extension_GL_NV_texture_border_clamp();
    load_extension_GL_NV_texture_compression_s3tc_update();
    load_extension_GL_NV_texture_compression_vtc();
    load_extension_GL_NV_texture_env_combine4();
    load_extension_GL_NV_texture_expand_normal();
    load_extension_GL_NV_texture_multisample();
    load_extension_GL_NV_texture_npot_2D_mipmap();
    load_extension_GL_NV_texture_rectangle();
    load_extension_GL_NV_texture_shader();
    load_extension_GL_NV_texture_shader2();
    load_extension_GL_NV_texture_shader3();
    load_extension_GL_NV_transform_feedback();
    load_extension_GL_NV_transform_feedback2();
    load_extension_GL_NV_uniform_buffer_unified_memory();
    load_extension_GL_NV_vdpau_interop();
    load_extension_GL_NV_vertex_array_range();
    load_extension_GL_NV_vertex_array_range2();
    load_extension_GL_NV_vertex_attrib_integer_64bit();
    load_extension_GL_NV_vertex_buffer_unified_memory();
    load_extension_GL_NV_vertex_program();
    load_extension_GL_NV_vertex_program1_1();
    load_extension_GL_NV_vertex_program2();
    load_extension_GL_NV_vertex_program2_option();
    load_extension_GL_NV_vertex_program3();
    load_extension_GL_NV_vertex_program4();
    load_extension_GL_NV_video_capture();
    load_extension_GL_NV_viewport_array();
    load_extension_GL_NV_viewport_array2();
    load_extension_GL_NV_viewport_swizzle();
    load_extension_GL_OES_EGL_image();
    load_extension_GL_OES_EGL_image_external();
    load_extension_GL_OES_EGL_image_external_essl3();
    load_extension_GL_OES_blend_equation_separate();
    load_extension_GL_OES_blend_func_separate();
    load_extension_GL_OES_blend_subtract();
    load_extension_GL_OES_byte_coordinates();
    load_extension_GL_OES_compressed_ETC1_RGB8_sub_texture();
    load_extension_GL_OES_compressed_ETC1_RGB8_texture();
    load_extension_GL_OES_compressed_paletted_texture();
    load_extension_GL_OES_copy_image();
    load_extension_GL_OES_depth24();
    load_extension_GL_OES_depth32();
    load_extension_GL_OES_depth_texture();
    load_extension_GL_OES_draw_buffers_indexed();
    load_extension_GL_OES_draw_elements_base_vertex();
    load_extension_GL_OES_draw_texture();
    load_extension_GL_OES_element_index_uint();
    load_extension_GL_OES_extended_matrix_palette();
    load_extension_GL_OES_fbo_render_mipmap();
    load_extension_GL_OES_fixed_point();
    load_extension_GL_OES_fragment_precision_high();
    load_extension_GL_OES_framebuffer_object();
    load_extension_GL_OES_geometry_point_size();
    load_extension_GL_OES_geometry_shader();
    load_extension_GL_OES_get_program_binary();
    load_extension_GL_OES_gpu_shader5();
    load_extension_GL_OES_mapbuffer();
    load_extension_GL_OES_matrix_get();
    load_extension_GL_OES_matrix_palette();
    load_extension_GL_OES_packed_depth_stencil();
    load_extension_GL_OES_point_size_array();
    load_extension_GL_OES_point_sprite();
    load_extension_GL_OES_primitive_bounding_box();
    load_extension_GL_OES_query_matrix();
    load_extension_GL_OES_read_format();
    load_extension_GL_OES_required_internalformat();
    load_extension_GL_OES_rgb8_rgba8();
    load_extension_GL_OES_sample_shading();
    load_extension_GL_OES_sample_variables();
    load_extension_GL_OES_shader_image_atomic();
    load_extension_GL_OES_shader_io_blocks();
    load_extension_GL_OES_shader_multisample_interpolation();
    load_extension_GL_OES_single_precision();
    load_extension_GL_OES_standard_derivatives();
    load_extension_GL_OES_stencil1();
    load_extension_GL_OES_stencil4();
    load_extension_GL_OES_stencil8();
    load_extension_GL_OES_stencil_wrap();
    load_extension_GL_OES_surfaceless_context();
    load_extension_GL_OES_tessellation_point_size();
    load_extension_GL_OES_tessellation_shader();
    load_extension_GL_OES_texture_3D();
    load_extension_GL_OES_texture_border_clamp();
    load_extension_GL_OES_texture_buffer();
    load_extension_GL_OES_texture_compression_astc();
    load_extension_GL_OES_texture_cube_map();
    load_extension_GL_OES_texture_cube_map_array();
    load_extension_GL_OES_texture_env_crossbar();
    load_extension_GL_OES_texture_float();
    load_extension_GL_OES_texture_float_linear();
    load_extension_GL_OES_texture_half_float();
    load_extension_GL_OES_texture_half_float_linear();
    load_extension_GL_OES_texture_mirrored_repeat();
    load_extension_GL_OES_texture_npot();
    load_extension_GL_OES_texture_stencil8();
    load_extension_GL_OES_texture_storage_multisample_2d_array();
    load_extension_GL_OES_texture_view();
    load_extension_GL_OES_vertex_array_object();
    load_extension_GL_OES_vertex_half_float();
    load_extension_GL_OES_vertex_type_10_10_10_2();
    load_extension_GL_OES_viewport_array();
    load_extension_GL_OML_interlace();
    load_extension_GL_OML_resample();
    load_extension_GL_OML_subsample();
    load_extension_GL_OVR_multiview();
    load_extension_GL_OVR_multiview2();
    load_extension_GL_OVR_multiview_multisampled_render_to_texture();
    load_extension_GL_PGI_misc_hints();
    load_extension_GL_PGI_vertex_hints();
    load_extension_GL_QCOM_alpha_test();
    load_extension_GL_QCOM_binning_control();
    load_extension_GL_QCOM_driver_control();
    load_extension_GL_QCOM_extended_get();
    load_extension_GL_QCOM_extended_get2();
    load_extension_GL_QCOM_perfmon_global_mode();
    load_extension_GL_QCOM_tiled_rendering();
    load_extension_GL_QCOM_writeonly_rendering();
    load_extension_GL_REND_screen_coordinates();
    load_extension_GL_S3_s3tc();
    load_extension_GL_SGIS_detail_texture();
    load_extension_GL_SGIS_fog_function();
    load_extension_GL_SGIS_generate_mipmap();
    load_extension_GL_SGIS_multisample();
    load_extension_GL_SGIS_pixel_texture();
    load_extension_GL_SGIS_point_line_texgen();
    load_extension_GL_SGIS_point_parameters();
    load_extension_GL_SGIS_sharpen_texture();
    load_extension_GL_SGIS_texture4D();
    load_extension_GL_SGIS_texture_border_clamp();
    load_extension_GL_SGIS_texture_color_mask();
    load_extension_GL_SGIS_texture_edge_clamp();
    load_extension_GL_SGIS_texture_filter4();
    load_extension_GL_SGIS_texture_lod();
    load_extension_GL_SGIS_texture_select();
    load_extension_GL_SGIX_async();
    load_extension_GL_SGIX_async_histogram();
    load_extension_GL_SGIX_async_pixel();
    load_extension_GL_SGIX_blend_alpha_minmax();
    load_extension_GL_SGIX_calligraphic_fragment();
    load_extension_GL_SGIX_clipmap();
    load_extension_GL_SGIX_convolution_accuracy();
    load_extension_GL_SGIX_depth_pass_instrument();
    load_extension_GL_SGIX_depth_texture();
    load_extension_GL_SGIX_flush_raster();
    load_extension_GL_SGIX_fog_offset();
    load_extension_GL_SGIX_fragment_lighting();
    load_extension_GL_SGIX_framezoom();
    load_extension_GL_SGIX_igloo_interface();
    load_extension_GL_SGIX_instruments();
    load_extension_GL_SGIX_interlace();
    load_extension_GL_SGIX_ir_instrument1();
    load_extension_GL_SGIX_list_priority();
    load_extension_GL_SGIX_pixel_texture();
    load_extension_GL_SGIX_pixel_tiles();
    load_extension_GL_SGIX_polynomial_ffd();
    load_extension_GL_SGIX_reference_plane();
    load_extension_GL_SGIX_resample();
    load_extension_GL_SGIX_scalebias_hint();
    load_extension_GL_SGIX_shadow();
    load_extension_GL_SGIX_shadow_ambient();
    load_extension_GL_SGIX_sprite();
    load_extension_GL_SGIX_subsample();
    load_extension_GL_SGIX_tag_sample_buffer();
    load_extension_GL_SGIX_texture_add_env();
    load_extension_GL_SGIX_texture_coordinate_clamp();
    load_extension_GL_SGIX_texture_lod_bias();
    load_extension_GL_SGIX_texture_multi_buffer();
    load_extension_GL_SGIX_texture_scale_bias();
    load_extension_GL_SGIX_vertex_preclip();
    load_extension_GL_SGIX_ycrcb();
    load_extension_GL_SGIX_ycrcb_subsample();
    load_extension_GL_SGIX_ycrcba();
    load_extension_GL_SGI_color_matrix();
    load_extension_GL_SGI_color_table();
    load_extension_GL_SGI_texture_color_table();
    load_extension_GL_SUNX_constant_data();
    load_extension_GL_SUN_convolution_border_modes();
    load_extension_GL_SUN_global_alpha();
    load_extension_GL_SUN_mesh_array();
    load_extension_GL_SUN_slice_accum();
    load_extension_GL_SUN_triangle_list();
    load_extension_GL_SUN_vertex();
    load_extension_GL_VIV_shader_binary();
    load_extension_GL_WIN_phong_shading();
    load_extension_GL_WIN_specular_fog();
}

#define GLFL_LOAD_FUNCTION(name) ((glfl::context *)(glfl::active_context()))->ptrs[glfl_func::name] = glfl::active_context()->function_loader("gl" #name);

static void load_version_gl(int major, int minor)
{
    switch (0x10000 * major + minor)
    {
      default:
      case 0x10000 * 4 + 5:
        GLFL_LOAD_FUNCTION(ClipControl);
        GLFL_LOAD_FUNCTION(CreateTransformFeedbacks);
        GLFL_LOAD_FUNCTION(TransformFeedbackBufferBase);
        GLFL_LOAD_FUNCTION(TransformFeedbackBufferRange);
        GLFL_LOAD_FUNCTION(GetTransformFeedbackiv);
        GLFL_LOAD_FUNCTION(GetTransformFeedbacki_v);
        GLFL_LOAD_FUNCTION(GetTransformFeedbacki64_v);
        GLFL_LOAD_FUNCTION(CreateBuffers);
        GLFL_LOAD_FUNCTION(NamedBufferStorage);
        GLFL_LOAD_FUNCTION(NamedBufferData);
        GLFL_LOAD_FUNCTION(NamedBufferSubData);
        GLFL_LOAD_FUNCTION(CopyNamedBufferSubData);
        GLFL_LOAD_FUNCTION(ClearNamedBufferData);
        GLFL_LOAD_FUNCTION(ClearNamedBufferSubData);
        GLFL_LOAD_FUNCTION(MapNamedBuffer);
        GLFL_LOAD_FUNCTION(MapNamedBufferRange);
        GLFL_LOAD_FUNCTION(UnmapNamedBuffer);
        GLFL_LOAD_FUNCTION(FlushMappedNamedBufferRange);
        GLFL_LOAD_FUNCTION(GetNamedBufferParameteriv);
        GLFL_LOAD_FUNCTION(GetNamedBufferParameteri64v);
        GLFL_LOAD_FUNCTION(GetNamedBufferPointerv);
        GLFL_LOAD_FUNCTION(GetNamedBufferSubData);
        GLFL_LOAD_FUNCTION(CreateFramebuffers);
        GLFL_LOAD_FUNCTION(NamedFramebufferRenderbuffer);
        GLFL_LOAD_FUNCTION(NamedFramebufferParameteri);
        GLFL_LOAD_FUNCTION(NamedFramebufferTexture);
        GLFL_LOAD_FUNCTION(NamedFramebufferTextureLayer);
        GLFL_LOAD_FUNCTION(NamedFramebufferDrawBuffer);
        GLFL_LOAD_FUNCTION(NamedFramebufferDrawBuffers);
        GLFL_LOAD_FUNCTION(NamedFramebufferReadBuffer);
        GLFL_LOAD_FUNCTION(InvalidateNamedFramebufferData);
        GLFL_LOAD_FUNCTION(InvalidateNamedFramebufferSubData);
        GLFL_LOAD_FUNCTION(ClearNamedFramebufferiv);
        GLFL_LOAD_FUNCTION(ClearNamedFramebufferuiv);
        GLFL_LOAD_FUNCTION(ClearNamedFramebufferfv);
        GLFL_LOAD_FUNCTION(ClearNamedFramebufferfi);
        GLFL_LOAD_FUNCTION(BlitNamedFramebuffer);
        GLFL_LOAD_FUNCTION(CheckNamedFramebufferStatus);
        GLFL_LOAD_FUNCTION(GetNamedFramebufferParameteriv);
        GLFL_LOAD_FUNCTION(GetNamedFramebufferAttachmentParameteriv);
        GLFL_LOAD_FUNCTION(CreateRenderbuffers);
        GLFL_LOAD_FUNCTION(NamedRenderbufferStorage);
        GLFL_LOAD_FUNCTION(NamedRenderbufferStorageMultisample);
        GLFL_LOAD_FUNCTION(GetNamedRenderbufferParameteriv);
        GLFL_LOAD_FUNCTION(CreateTextures);
        GLFL_LOAD_FUNCTION(TextureBuffer);
        GLFL_LOAD_FUNCTION(TextureBufferRange);
        GLFL_LOAD_FUNCTION(TextureStorage1D);
        GLFL_LOAD_FUNCTION(TextureStorage2D);
        GLFL_LOAD_FUNCTION(TextureStorage3D);
        GLFL_LOAD_FUNCTION(TextureStorage2DMultisample);
        GLFL_LOAD_FUNCTION(TextureStorage3DMultisample);
        GLFL_LOAD_FUNCTION(TextureSubImage1D);
        GLFL_LOAD_FUNCTION(TextureSubImage2D);
        GLFL_LOAD_FUNCTION(TextureSubImage3D);
        GLFL_LOAD_FUNCTION(CompressedTextureSubImage1D);
        GLFL_LOAD_FUNCTION(CompressedTextureSubImage2D);
        GLFL_LOAD_FUNCTION(CompressedTextureSubImage3D);
        GLFL_LOAD_FUNCTION(CopyTextureSubImage1D);
        GLFL_LOAD_FUNCTION(CopyTextureSubImage2D);
        GLFL_LOAD_FUNCTION(CopyTextureSubImage3D);
        GLFL_LOAD_FUNCTION(TextureParameterf);
        GLFL_LOAD_FUNCTION(TextureParameterfv);
        GLFL_LOAD_FUNCTION(TextureParameteri);
        GLFL_LOAD_FUNCTION(TextureParameterIiv);
        GLFL_LOAD_FUNCTION(TextureParameterIuiv);
        GLFL_LOAD_FUNCTION(TextureParameteriv);
        GLFL_LOAD_FUNCTION(GenerateTextureMipmap);
        GLFL_LOAD_FUNCTION(BindTextureUnit);
        GLFL_LOAD_FUNCTION(GetTextureImage);
        GLFL_LOAD_FUNCTION(GetCompressedTextureImage);
        GLFL_LOAD_FUNCTION(GetTextureLevelParameterfv);
        GLFL_LOAD_FUNCTION(GetTextureLevelParameteriv);
        GLFL_LOAD_FUNCTION(GetTextureParameterfv);
        GLFL_LOAD_FUNCTION(GetTextureParameterIiv);
        GLFL_LOAD_FUNCTION(GetTextureParameterIuiv);
        GLFL_LOAD_FUNCTION(GetTextureParameteriv);
        GLFL_LOAD_FUNCTION(CreateVertexArrays);
        GLFL_LOAD_FUNCTION(DisableVertexArrayAttrib);
        GLFL_LOAD_FUNCTION(EnableVertexArrayAttrib);
        GLFL_LOAD_FUNCTION(VertexArrayElementBuffer);
        GLFL_LOAD_FUNCTION(VertexArrayVertexBuffer);
        GLFL_LOAD_FUNCTION(VertexArrayVertexBuffers);
        GLFL_LOAD_FUNCTION(VertexArrayAttribBinding);
        GLFL_LOAD_FUNCTION(VertexArrayAttribFormat);
        GLFL_LOAD_FUNCTION(VertexArrayAttribIFormat);
        GLFL_LOAD_FUNCTION(VertexArrayAttribLFormat);
        GLFL_LOAD_FUNCTION(VertexArrayBindingDivisor);
        GLFL_LOAD_FUNCTION(GetVertexArrayiv);
        GLFL_LOAD_FUNCTION(GetVertexArrayIndexediv);
        GLFL_LOAD_FUNCTION(GetVertexArrayIndexed64iv);
        GLFL_LOAD_FUNCTION(CreateSamplers);
        GLFL_LOAD_FUNCTION(CreateProgramPipelines);
        GLFL_LOAD_FUNCTION(CreateQueries);
        GLFL_LOAD_FUNCTION(GetQueryBufferObjecti64v);
        GLFL_LOAD_FUNCTION(GetQueryBufferObjectiv);
        GLFL_LOAD_FUNCTION(GetQueryBufferObjectui64v);
        GLFL_LOAD_FUNCTION(GetQueryBufferObjectuiv);
        GLFL_LOAD_FUNCTION(MemoryBarrierByRegion);
        GLFL_LOAD_FUNCTION(GetTextureSubImage);
        GLFL_LOAD_FUNCTION(GetCompressedTextureSubImage);
        GLFL_LOAD_FUNCTION(GetGraphicsResetStatus);
        GLFL_LOAD_FUNCTION(GetnCompressedTexImage);
        GLFL_LOAD_FUNCTION(GetnTexImage);
        GLFL_LOAD_FUNCTION(GetnUniformdv);
        GLFL_LOAD_FUNCTION(GetnUniformfv);
        GLFL_LOAD_FUNCTION(GetnUniformiv);
        GLFL_LOAD_FUNCTION(GetnUniformuiv);
        GLFL_LOAD_FUNCTION(ReadnPixels);
        GLFL_LOAD_FUNCTION(GetnMapdv);
        GLFL_LOAD_FUNCTION(GetnMapfv);
        GLFL_LOAD_FUNCTION(GetnMapiv);
        GLFL_LOAD_FUNCTION(GetnPixelMapfv);
        GLFL_LOAD_FUNCTION(GetnPixelMapuiv);
        GLFL_LOAD_FUNCTION(GetnPixelMapusv);
        GLFL_LOAD_FUNCTION(GetnPolygonStipple);
        GLFL_LOAD_FUNCTION(GetnColorTable);
        GLFL_LOAD_FUNCTION(GetnConvolutionFilter);
        GLFL_LOAD_FUNCTION(GetnSeparableFilter);
        GLFL_LOAD_FUNCTION(GetnHistogram);
        GLFL_LOAD_FUNCTION(GetnMinmax);
        GLFL_LOAD_FUNCTION(TextureBarrier);
      case 0x10000 * 4 + 4:
        GLFL_LOAD_FUNCTION(BufferStorage);
        GLFL_LOAD_FUNCTION(ClearTexImage);
        GLFL_LOAD_FUNCTION(ClearTexSubImage);
        GLFL_LOAD_FUNCTION(BindBuffersBase);
        GLFL_LOAD_FUNCTION(BindBuffersRange);
        GLFL_LOAD_FUNCTION(BindTextures);
        GLFL_LOAD_FUNCTION(BindSamplers);
        GLFL_LOAD_FUNCTION(BindImageTextures);
        GLFL_LOAD_FUNCTION(BindVertexBuffers);
      case 0x10000 * 4 + 3:
        GLFL_LOAD_FUNCTION(ClearBufferData);
        GLFL_LOAD_FUNCTION(ClearBufferSubData);
        GLFL_LOAD_FUNCTION(DispatchCompute);
        GLFL_LOAD_FUNCTION(DispatchComputeIndirect);
        GLFL_LOAD_FUNCTION(CopyImageSubData);
        GLFL_LOAD_FUNCTION(FramebufferParameteri);
        GLFL_LOAD_FUNCTION(GetFramebufferParameteriv);
        GLFL_LOAD_FUNCTION(GetInternalformati64v);
        GLFL_LOAD_FUNCTION(InvalidateTexSubImage);
        GLFL_LOAD_FUNCTION(InvalidateTexImage);
        GLFL_LOAD_FUNCTION(InvalidateBufferSubData);
        GLFL_LOAD_FUNCTION(InvalidateBufferData);
        GLFL_LOAD_FUNCTION(InvalidateFramebuffer);
        GLFL_LOAD_FUNCTION(InvalidateSubFramebuffer);
        GLFL_LOAD_FUNCTION(MultiDrawArraysIndirect);
        GLFL_LOAD_FUNCTION(MultiDrawElementsIndirect);
        GLFL_LOAD_FUNCTION(GetProgramInterfaceiv);
        GLFL_LOAD_FUNCTION(GetProgramResourceIndex);
        GLFL_LOAD_FUNCTION(GetProgramResourceName);
        GLFL_LOAD_FUNCTION(GetProgramResourceiv);
        GLFL_LOAD_FUNCTION(GetProgramResourceLocation);
        GLFL_LOAD_FUNCTION(GetProgramResourceLocationIndex);
        GLFL_LOAD_FUNCTION(ShaderStorageBlockBinding);
        GLFL_LOAD_FUNCTION(TexBufferRange);
        GLFL_LOAD_FUNCTION(TexStorage2DMultisample);
        GLFL_LOAD_FUNCTION(TexStorage3DMultisample);
        GLFL_LOAD_FUNCTION(TextureView);
        GLFL_LOAD_FUNCTION(BindVertexBuffer);
        GLFL_LOAD_FUNCTION(VertexAttribFormat);
        GLFL_LOAD_FUNCTION(VertexAttribIFormat);
        GLFL_LOAD_FUNCTION(VertexAttribLFormat);
        GLFL_LOAD_FUNCTION(VertexAttribBinding);
        GLFL_LOAD_FUNCTION(VertexBindingDivisor);
        GLFL_LOAD_FUNCTION(DebugMessageControl);
        GLFL_LOAD_FUNCTION(DebugMessageInsert);
        GLFL_LOAD_FUNCTION(DebugMessageCallback);
        GLFL_LOAD_FUNCTION(GetDebugMessageLog);
        GLFL_LOAD_FUNCTION(PushDebugGroup);
        GLFL_LOAD_FUNCTION(PopDebugGroup);
        GLFL_LOAD_FUNCTION(ObjectLabel);
        GLFL_LOAD_FUNCTION(GetObjectLabel);
        GLFL_LOAD_FUNCTION(ObjectPtrLabel);
        GLFL_LOAD_FUNCTION(GetObjectPtrLabel);
        GLFL_LOAD_FUNCTION(GetPointerv);
        GLFL_LOAD_FUNCTION(GetPointerv);
      case 0x10000 * 4 + 2:
        GLFL_LOAD_FUNCTION(DrawArraysInstancedBaseInstance);
        GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseInstance);
        GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertexBaseInstance);
        GLFL_LOAD_FUNCTION(GetInternalformativ);
        GLFL_LOAD_FUNCTION(GetActiveAtomicCounterBufferiv);
        GLFL_LOAD_FUNCTION(BindImageTexture);
        GLFL_LOAD_FUNCTION(MemoryBarrier);
        GLFL_LOAD_FUNCTION(TexStorage1D);
        GLFL_LOAD_FUNCTION(TexStorage2D);
        GLFL_LOAD_FUNCTION(TexStorage3D);
        GLFL_LOAD_FUNCTION(DrawTransformFeedbackInstanced);
        GLFL_LOAD_FUNCTION(DrawTransformFeedbackStreamInstanced);
      case 0x10000 * 4 + 1:
        GLFL_LOAD_FUNCTION(ReleaseShaderCompiler);
        GLFL_LOAD_FUNCTION(ShaderBinary);
        GLFL_LOAD_FUNCTION(GetShaderPrecisionFormat);
        GLFL_LOAD_FUNCTION(DepthRangef);
        GLFL_LOAD_FUNCTION(ClearDepthf);
        GLFL_LOAD_FUNCTION(GetProgramBinary);
        GLFL_LOAD_FUNCTION(ProgramBinary);
        GLFL_LOAD_FUNCTION(ProgramParameteri);
        GLFL_LOAD_FUNCTION(UseProgramStages);
        GLFL_LOAD_FUNCTION(ActiveShaderProgram);
        GLFL_LOAD_FUNCTION(CreateShaderProgramv);
        GLFL_LOAD_FUNCTION(BindProgramPipeline);
        GLFL_LOAD_FUNCTION(DeleteProgramPipelines);
        GLFL_LOAD_FUNCTION(GenProgramPipelines);
        GLFL_LOAD_FUNCTION(IsProgramPipeline);
        GLFL_LOAD_FUNCTION(GetProgramPipelineiv);
        GLFL_LOAD_FUNCTION(ProgramUniform1i);
        GLFL_LOAD_FUNCTION(ProgramUniform1iv);
        GLFL_LOAD_FUNCTION(ProgramUniform1f);
        GLFL_LOAD_FUNCTION(ProgramUniform1fv);
        GLFL_LOAD_FUNCTION(ProgramUniform1d);
        GLFL_LOAD_FUNCTION(ProgramUniform1dv);
        GLFL_LOAD_FUNCTION(ProgramUniform1ui);
        GLFL_LOAD_FUNCTION(ProgramUniform1uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform2i);
        GLFL_LOAD_FUNCTION(ProgramUniform2iv);
        GLFL_LOAD_FUNCTION(ProgramUniform2f);
        GLFL_LOAD_FUNCTION(ProgramUniform2fv);
        GLFL_LOAD_FUNCTION(ProgramUniform2d);
        GLFL_LOAD_FUNCTION(ProgramUniform2dv);
        GLFL_LOAD_FUNCTION(ProgramUniform2ui);
        GLFL_LOAD_FUNCTION(ProgramUniform2uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform3i);
        GLFL_LOAD_FUNCTION(ProgramUniform3iv);
        GLFL_LOAD_FUNCTION(ProgramUniform3f);
        GLFL_LOAD_FUNCTION(ProgramUniform3fv);
        GLFL_LOAD_FUNCTION(ProgramUniform3d);
        GLFL_LOAD_FUNCTION(ProgramUniform3dv);
        GLFL_LOAD_FUNCTION(ProgramUniform3ui);
        GLFL_LOAD_FUNCTION(ProgramUniform3uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform4i);
        GLFL_LOAD_FUNCTION(ProgramUniform4iv);
        GLFL_LOAD_FUNCTION(ProgramUniform4f);
        GLFL_LOAD_FUNCTION(ProgramUniform4fv);
        GLFL_LOAD_FUNCTION(ProgramUniform4d);
        GLFL_LOAD_FUNCTION(ProgramUniform4dv);
        GLFL_LOAD_FUNCTION(ProgramUniform4ui);
        GLFL_LOAD_FUNCTION(ProgramUniform4uiv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3dv);
        GLFL_LOAD_FUNCTION(ValidateProgramPipeline);
        GLFL_LOAD_FUNCTION(GetProgramPipelineInfoLog);
        GLFL_LOAD_FUNCTION(VertexAttribL1d);
        GLFL_LOAD_FUNCTION(VertexAttribL2d);
        GLFL_LOAD_FUNCTION(VertexAttribL3d);
        GLFL_LOAD_FUNCTION(VertexAttribL4d);
        GLFL_LOAD_FUNCTION(VertexAttribL1dv);
        GLFL_LOAD_FUNCTION(VertexAttribL2dv);
        GLFL_LOAD_FUNCTION(VertexAttribL3dv);
        GLFL_LOAD_FUNCTION(VertexAttribL4dv);
        GLFL_LOAD_FUNCTION(VertexAttribLPointer);
        GLFL_LOAD_FUNCTION(GetVertexAttribLdv);
        GLFL_LOAD_FUNCTION(ViewportArrayv);
        GLFL_LOAD_FUNCTION(ViewportIndexedf);
        GLFL_LOAD_FUNCTION(ViewportIndexedfv);
        GLFL_LOAD_FUNCTION(ScissorArrayv);
        GLFL_LOAD_FUNCTION(ScissorIndexed);
        GLFL_LOAD_FUNCTION(ScissorIndexedv);
        GLFL_LOAD_FUNCTION(DepthRangeArrayv);
        GLFL_LOAD_FUNCTION(DepthRangeIndexed);
        GLFL_LOAD_FUNCTION(GetFloati_v);
        GLFL_LOAD_FUNCTION(GetDoublei_v);
      case 0x10000 * 4 + 0:
        GLFL_LOAD_FUNCTION(MinSampleShading);
        GLFL_LOAD_FUNCTION(BlendEquationi);
        GLFL_LOAD_FUNCTION(BlendEquationSeparatei);
        GLFL_LOAD_FUNCTION(BlendFunci);
        GLFL_LOAD_FUNCTION(BlendFuncSeparatei);
        GLFL_LOAD_FUNCTION(DrawArraysIndirect);
        GLFL_LOAD_FUNCTION(DrawElementsIndirect);
        GLFL_LOAD_FUNCTION(Uniform1d);
        GLFL_LOAD_FUNCTION(Uniform2d);
        GLFL_LOAD_FUNCTION(Uniform3d);
        GLFL_LOAD_FUNCTION(Uniform4d);
        GLFL_LOAD_FUNCTION(Uniform1dv);
        GLFL_LOAD_FUNCTION(Uniform2dv);
        GLFL_LOAD_FUNCTION(Uniform3dv);
        GLFL_LOAD_FUNCTION(Uniform4dv);
        GLFL_LOAD_FUNCTION(UniformMatrix2dv);
        GLFL_LOAD_FUNCTION(UniformMatrix3dv);
        GLFL_LOAD_FUNCTION(UniformMatrix4dv);
        GLFL_LOAD_FUNCTION(UniformMatrix2x3dv);
        GLFL_LOAD_FUNCTION(UniformMatrix2x4dv);
        GLFL_LOAD_FUNCTION(UniformMatrix3x2dv);
        GLFL_LOAD_FUNCTION(UniformMatrix3x4dv);
        GLFL_LOAD_FUNCTION(UniformMatrix4x2dv);
        GLFL_LOAD_FUNCTION(UniformMatrix4x3dv);
        GLFL_LOAD_FUNCTION(GetUniformdv);
        GLFL_LOAD_FUNCTION(GetSubroutineUniformLocation);
        GLFL_LOAD_FUNCTION(GetSubroutineIndex);
        GLFL_LOAD_FUNCTION(GetActiveSubroutineUniformiv);
        GLFL_LOAD_FUNCTION(GetActiveSubroutineUniformName);
        GLFL_LOAD_FUNCTION(GetActiveSubroutineName);
        GLFL_LOAD_FUNCTION(UniformSubroutinesuiv);
        GLFL_LOAD_FUNCTION(GetUniformSubroutineuiv);
        GLFL_LOAD_FUNCTION(GetProgramStageiv);
        GLFL_LOAD_FUNCTION(PatchParameteri);
        GLFL_LOAD_FUNCTION(PatchParameterfv);
        GLFL_LOAD_FUNCTION(BindTransformFeedback);
        GLFL_LOAD_FUNCTION(DeleteTransformFeedbacks);
        GLFL_LOAD_FUNCTION(GenTransformFeedbacks);
        GLFL_LOAD_FUNCTION(IsTransformFeedback);
        GLFL_LOAD_FUNCTION(PauseTransformFeedback);
        GLFL_LOAD_FUNCTION(ResumeTransformFeedback);
        GLFL_LOAD_FUNCTION(DrawTransformFeedback);
        GLFL_LOAD_FUNCTION(DrawTransformFeedbackStream);
        GLFL_LOAD_FUNCTION(BeginQueryIndexed);
        GLFL_LOAD_FUNCTION(EndQueryIndexed);
        GLFL_LOAD_FUNCTION(GetQueryIndexediv);
      case 0x10000 * 3 + 3:
        GLFL_LOAD_FUNCTION(BindFragDataLocationIndexed);
        GLFL_LOAD_FUNCTION(GetFragDataIndex);
        GLFL_LOAD_FUNCTION(GenSamplers);
        GLFL_LOAD_FUNCTION(DeleteSamplers);
        GLFL_LOAD_FUNCTION(IsSampler);
        GLFL_LOAD_FUNCTION(BindSampler);
        GLFL_LOAD_FUNCTION(SamplerParameteri);
        GLFL_LOAD_FUNCTION(SamplerParameteriv);
        GLFL_LOAD_FUNCTION(SamplerParameterf);
        GLFL_LOAD_FUNCTION(SamplerParameterfv);
        GLFL_LOAD_FUNCTION(SamplerParameterIiv);
        GLFL_LOAD_FUNCTION(SamplerParameterIuiv);
        GLFL_LOAD_FUNCTION(GetSamplerParameteriv);
        GLFL_LOAD_FUNCTION(GetSamplerParameterIiv);
        GLFL_LOAD_FUNCTION(GetSamplerParameterfv);
        GLFL_LOAD_FUNCTION(GetSamplerParameterIuiv);
        GLFL_LOAD_FUNCTION(QueryCounter);
        GLFL_LOAD_FUNCTION(GetQueryObjecti64v);
        GLFL_LOAD_FUNCTION(GetQueryObjectui64v);
        GLFL_LOAD_FUNCTION(VertexAttribDivisor);
        GLFL_LOAD_FUNCTION(VertexAttribP1ui);
        GLFL_LOAD_FUNCTION(VertexAttribP1uiv);
        GLFL_LOAD_FUNCTION(VertexAttribP2ui);
        GLFL_LOAD_FUNCTION(VertexAttribP2uiv);
        GLFL_LOAD_FUNCTION(VertexAttribP3ui);
        GLFL_LOAD_FUNCTION(VertexAttribP3uiv);
        GLFL_LOAD_FUNCTION(VertexAttribP4ui);
        GLFL_LOAD_FUNCTION(VertexAttribP4uiv);
        GLFL_LOAD_FUNCTION(VertexP2ui);
        GLFL_LOAD_FUNCTION(VertexP2uiv);
        GLFL_LOAD_FUNCTION(VertexP3ui);
        GLFL_LOAD_FUNCTION(VertexP3uiv);
        GLFL_LOAD_FUNCTION(VertexP4ui);
        GLFL_LOAD_FUNCTION(VertexP4uiv);
        GLFL_LOAD_FUNCTION(TexCoordP1ui);
        GLFL_LOAD_FUNCTION(TexCoordP1uiv);
        GLFL_LOAD_FUNCTION(TexCoordP2ui);
        GLFL_LOAD_FUNCTION(TexCoordP2uiv);
        GLFL_LOAD_FUNCTION(TexCoordP3ui);
        GLFL_LOAD_FUNCTION(TexCoordP3uiv);
        GLFL_LOAD_FUNCTION(TexCoordP4ui);
        GLFL_LOAD_FUNCTION(TexCoordP4uiv);
        GLFL_LOAD_FUNCTION(MultiTexCoordP1ui);
        GLFL_LOAD_FUNCTION(MultiTexCoordP1uiv);
        GLFL_LOAD_FUNCTION(MultiTexCoordP2ui);
        GLFL_LOAD_FUNCTION(MultiTexCoordP2uiv);
        GLFL_LOAD_FUNCTION(MultiTexCoordP3ui);
        GLFL_LOAD_FUNCTION(MultiTexCoordP3uiv);
        GLFL_LOAD_FUNCTION(MultiTexCoordP4ui);
        GLFL_LOAD_FUNCTION(MultiTexCoordP4uiv);
        GLFL_LOAD_FUNCTION(NormalP3ui);
        GLFL_LOAD_FUNCTION(NormalP3uiv);
        GLFL_LOAD_FUNCTION(ColorP3ui);
        GLFL_LOAD_FUNCTION(ColorP3uiv);
        GLFL_LOAD_FUNCTION(ColorP4ui);
        GLFL_LOAD_FUNCTION(ColorP4uiv);
        GLFL_LOAD_FUNCTION(SecondaryColorP3ui);
        GLFL_LOAD_FUNCTION(SecondaryColorP3uiv);
      case 0x10000 * 3 + 2:
        GLFL_LOAD_FUNCTION(DrawElementsBaseVertex);
        GLFL_LOAD_FUNCTION(DrawRangeElementsBaseVertex);
        GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertex);
        GLFL_LOAD_FUNCTION(MultiDrawElementsBaseVertex);
        GLFL_LOAD_FUNCTION(ProvokingVertex);
        GLFL_LOAD_FUNCTION(FenceSync);
        GLFL_LOAD_FUNCTION(IsSync);
        GLFL_LOAD_FUNCTION(DeleteSync);
        GLFL_LOAD_FUNCTION(ClientWaitSync);
        GLFL_LOAD_FUNCTION(WaitSync);
        GLFL_LOAD_FUNCTION(GetInteger64v);
        GLFL_LOAD_FUNCTION(GetSynciv);
        GLFL_LOAD_FUNCTION(GetInteger64i_v);
        GLFL_LOAD_FUNCTION(GetBufferParameteri64v);
        GLFL_LOAD_FUNCTION(FramebufferTexture);
        GLFL_LOAD_FUNCTION(TexImage2DMultisample);
        GLFL_LOAD_FUNCTION(TexImage3DMultisample);
        GLFL_LOAD_FUNCTION(GetMultisamplefv);
        GLFL_LOAD_FUNCTION(SampleMaski);
      case 0x10000 * 3 + 1:
        GLFL_LOAD_FUNCTION(DrawArraysInstanced);
        GLFL_LOAD_FUNCTION(DrawElementsInstanced);
        GLFL_LOAD_FUNCTION(TexBuffer);
        GLFL_LOAD_FUNCTION(PrimitiveRestartIndex);
        GLFL_LOAD_FUNCTION(CopyBufferSubData);
        GLFL_LOAD_FUNCTION(GetUniformIndices);
        GLFL_LOAD_FUNCTION(GetActiveUniformsiv);
        GLFL_LOAD_FUNCTION(GetActiveUniformName);
        GLFL_LOAD_FUNCTION(GetUniformBlockIndex);
        GLFL_LOAD_FUNCTION(GetActiveUniformBlockiv);
        GLFL_LOAD_FUNCTION(GetActiveUniformBlockName);
        GLFL_LOAD_FUNCTION(UniformBlockBinding);
        GLFL_LOAD_FUNCTION(BindBufferRange);
        GLFL_LOAD_FUNCTION(BindBufferBase);
        GLFL_LOAD_FUNCTION(GetIntegeri_v);
      case 0x10000 * 3 + 0:
        GLFL_LOAD_FUNCTION(ColorMaski);
        GLFL_LOAD_FUNCTION(GetBooleani_v);
        GLFL_LOAD_FUNCTION(GetIntegeri_v);
        GLFL_LOAD_FUNCTION(Enablei);
        GLFL_LOAD_FUNCTION(Disablei);
        GLFL_LOAD_FUNCTION(IsEnabledi);
        GLFL_LOAD_FUNCTION(BeginTransformFeedback);
        GLFL_LOAD_FUNCTION(EndTransformFeedback);
        GLFL_LOAD_FUNCTION(BindBufferRange);
        GLFL_LOAD_FUNCTION(BindBufferBase);
        GLFL_LOAD_FUNCTION(TransformFeedbackVaryings);
        GLFL_LOAD_FUNCTION(GetTransformFeedbackVarying);
        GLFL_LOAD_FUNCTION(ClampColor);
        GLFL_LOAD_FUNCTION(BeginConditionalRender);
        GLFL_LOAD_FUNCTION(EndConditionalRender);
        GLFL_LOAD_FUNCTION(VertexAttribIPointer);
        GLFL_LOAD_FUNCTION(GetVertexAttribIiv);
        GLFL_LOAD_FUNCTION(GetVertexAttribIuiv);
        GLFL_LOAD_FUNCTION(VertexAttribI1i);
        GLFL_LOAD_FUNCTION(VertexAttribI2i);
        GLFL_LOAD_FUNCTION(VertexAttribI3i);
        GLFL_LOAD_FUNCTION(VertexAttribI4i);
        GLFL_LOAD_FUNCTION(VertexAttribI1ui);
        GLFL_LOAD_FUNCTION(VertexAttribI2ui);
        GLFL_LOAD_FUNCTION(VertexAttribI3ui);
        GLFL_LOAD_FUNCTION(VertexAttribI4ui);
        GLFL_LOAD_FUNCTION(VertexAttribI1iv);
        GLFL_LOAD_FUNCTION(VertexAttribI2iv);
        GLFL_LOAD_FUNCTION(VertexAttribI3iv);
        GLFL_LOAD_FUNCTION(VertexAttribI4iv);
        GLFL_LOAD_FUNCTION(VertexAttribI1uiv);
        GLFL_LOAD_FUNCTION(VertexAttribI2uiv);
        GLFL_LOAD_FUNCTION(VertexAttribI3uiv);
        GLFL_LOAD_FUNCTION(VertexAttribI4uiv);
        GLFL_LOAD_FUNCTION(VertexAttribI4bv);
        GLFL_LOAD_FUNCTION(VertexAttribI4sv);
        GLFL_LOAD_FUNCTION(VertexAttribI4ubv);
        GLFL_LOAD_FUNCTION(VertexAttribI4usv);
        GLFL_LOAD_FUNCTION(GetUniformuiv);
        GLFL_LOAD_FUNCTION(BindFragDataLocation);
        GLFL_LOAD_FUNCTION(GetFragDataLocation);
        GLFL_LOAD_FUNCTION(Uniform1ui);
        GLFL_LOAD_FUNCTION(Uniform2ui);
        GLFL_LOAD_FUNCTION(Uniform3ui);
        GLFL_LOAD_FUNCTION(Uniform4ui);
        GLFL_LOAD_FUNCTION(Uniform1uiv);
        GLFL_LOAD_FUNCTION(Uniform2uiv);
        GLFL_LOAD_FUNCTION(Uniform3uiv);
        GLFL_LOAD_FUNCTION(Uniform4uiv);
        GLFL_LOAD_FUNCTION(TexParameterIiv);
        GLFL_LOAD_FUNCTION(TexParameterIuiv);
        GLFL_LOAD_FUNCTION(GetTexParameterIiv);
        GLFL_LOAD_FUNCTION(GetTexParameterIuiv);
        GLFL_LOAD_FUNCTION(ClearBufferiv);
        GLFL_LOAD_FUNCTION(ClearBufferuiv);
        GLFL_LOAD_FUNCTION(ClearBufferfv);
        GLFL_LOAD_FUNCTION(ClearBufferfi);
        GLFL_LOAD_FUNCTION(GetStringi);
        GLFL_LOAD_FUNCTION(IsRenderbuffer);
        GLFL_LOAD_FUNCTION(BindRenderbuffer);
        GLFL_LOAD_FUNCTION(DeleteRenderbuffers);
        GLFL_LOAD_FUNCTION(GenRenderbuffers);
        GLFL_LOAD_FUNCTION(RenderbufferStorage);
        GLFL_LOAD_FUNCTION(GetRenderbufferParameteriv);
        GLFL_LOAD_FUNCTION(IsFramebuffer);
        GLFL_LOAD_FUNCTION(BindFramebuffer);
        GLFL_LOAD_FUNCTION(DeleteFramebuffers);
        GLFL_LOAD_FUNCTION(GenFramebuffers);
        GLFL_LOAD_FUNCTION(CheckFramebufferStatus);
        GLFL_LOAD_FUNCTION(FramebufferTexture1D);
        GLFL_LOAD_FUNCTION(FramebufferTexture2D);
        GLFL_LOAD_FUNCTION(FramebufferTexture3D);
        GLFL_LOAD_FUNCTION(FramebufferRenderbuffer);
        GLFL_LOAD_FUNCTION(GetFramebufferAttachmentParameteriv);
        GLFL_LOAD_FUNCTION(GenerateMipmap);
        GLFL_LOAD_FUNCTION(BlitFramebuffer);
        GLFL_LOAD_FUNCTION(RenderbufferStorageMultisample);
        GLFL_LOAD_FUNCTION(FramebufferTextureLayer);
        GLFL_LOAD_FUNCTION(MapBufferRange);
        GLFL_LOAD_FUNCTION(FlushMappedBufferRange);
        GLFL_LOAD_FUNCTION(BindVertexArray);
        GLFL_LOAD_FUNCTION(DeleteVertexArrays);
        GLFL_LOAD_FUNCTION(GenVertexArrays);
        GLFL_LOAD_FUNCTION(IsVertexArray);
      case 0x10000 * 2 + 1:
        GLFL_LOAD_FUNCTION(UniformMatrix2x3fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3x2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix2x4fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4x2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3x4fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4x3fv);
      case 0x10000 * 2 + 0:
        GLFL_LOAD_FUNCTION(BlendEquationSeparate);
        GLFL_LOAD_FUNCTION(DrawBuffers);
        GLFL_LOAD_FUNCTION(StencilOpSeparate);
        GLFL_LOAD_FUNCTION(StencilFuncSeparate);
        GLFL_LOAD_FUNCTION(StencilMaskSeparate);
        GLFL_LOAD_FUNCTION(AttachShader);
        GLFL_LOAD_FUNCTION(BindAttribLocation);
        GLFL_LOAD_FUNCTION(CompileShader);
        GLFL_LOAD_FUNCTION(CreateProgram);
        GLFL_LOAD_FUNCTION(CreateShader);
        GLFL_LOAD_FUNCTION(DeleteProgram);
        GLFL_LOAD_FUNCTION(DeleteShader);
        GLFL_LOAD_FUNCTION(DetachShader);
        GLFL_LOAD_FUNCTION(DisableVertexAttribArray);
        GLFL_LOAD_FUNCTION(EnableVertexAttribArray);
        GLFL_LOAD_FUNCTION(GetActiveAttrib);
        GLFL_LOAD_FUNCTION(GetActiveUniform);
        GLFL_LOAD_FUNCTION(GetAttachedShaders);
        GLFL_LOAD_FUNCTION(GetAttribLocation);
        GLFL_LOAD_FUNCTION(GetProgramiv);
        GLFL_LOAD_FUNCTION(GetProgramInfoLog);
        GLFL_LOAD_FUNCTION(GetShaderiv);
        GLFL_LOAD_FUNCTION(GetShaderInfoLog);
        GLFL_LOAD_FUNCTION(GetShaderSource);
        GLFL_LOAD_FUNCTION(GetUniformLocation);
        GLFL_LOAD_FUNCTION(GetUniformfv);
        GLFL_LOAD_FUNCTION(GetUniformiv);
        GLFL_LOAD_FUNCTION(GetVertexAttribdv);
        GLFL_LOAD_FUNCTION(GetVertexAttribfv);
        GLFL_LOAD_FUNCTION(GetVertexAttribiv);
        GLFL_LOAD_FUNCTION(GetVertexAttribPointerv);
        GLFL_LOAD_FUNCTION(IsProgram);
        GLFL_LOAD_FUNCTION(IsShader);
        GLFL_LOAD_FUNCTION(LinkProgram);
        GLFL_LOAD_FUNCTION(ShaderSource);
        GLFL_LOAD_FUNCTION(UseProgram);
        GLFL_LOAD_FUNCTION(Uniform1f);
        GLFL_LOAD_FUNCTION(Uniform2f);
        GLFL_LOAD_FUNCTION(Uniform3f);
        GLFL_LOAD_FUNCTION(Uniform4f);
        GLFL_LOAD_FUNCTION(Uniform1i);
        GLFL_LOAD_FUNCTION(Uniform2i);
        GLFL_LOAD_FUNCTION(Uniform3i);
        GLFL_LOAD_FUNCTION(Uniform4i);
        GLFL_LOAD_FUNCTION(Uniform1fv);
        GLFL_LOAD_FUNCTION(Uniform2fv);
        GLFL_LOAD_FUNCTION(Uniform3fv);
        GLFL_LOAD_FUNCTION(Uniform4fv);
        GLFL_LOAD_FUNCTION(Uniform1iv);
        GLFL_LOAD_FUNCTION(Uniform2iv);
        GLFL_LOAD_FUNCTION(Uniform3iv);
        GLFL_LOAD_FUNCTION(Uniform4iv);
        GLFL_LOAD_FUNCTION(UniformMatrix2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4fv);
        GLFL_LOAD_FUNCTION(ValidateProgram);
        GLFL_LOAD_FUNCTION(VertexAttrib1d);
        GLFL_LOAD_FUNCTION(VertexAttrib1dv);
        GLFL_LOAD_FUNCTION(VertexAttrib1f);
        GLFL_LOAD_FUNCTION(VertexAttrib1fv);
        GLFL_LOAD_FUNCTION(VertexAttrib1s);
        GLFL_LOAD_FUNCTION(VertexAttrib1sv);
        GLFL_LOAD_FUNCTION(VertexAttrib2d);
        GLFL_LOAD_FUNCTION(VertexAttrib2dv);
        GLFL_LOAD_FUNCTION(VertexAttrib2f);
        GLFL_LOAD_FUNCTION(VertexAttrib2fv);
        GLFL_LOAD_FUNCTION(VertexAttrib2s);
        GLFL_LOAD_FUNCTION(VertexAttrib2sv);
        GLFL_LOAD_FUNCTION(VertexAttrib3d);
        GLFL_LOAD_FUNCTION(VertexAttrib3dv);
        GLFL_LOAD_FUNCTION(VertexAttrib3f);
        GLFL_LOAD_FUNCTION(VertexAttrib3fv);
        GLFL_LOAD_FUNCTION(VertexAttrib3s);
        GLFL_LOAD_FUNCTION(VertexAttrib3sv);
        GLFL_LOAD_FUNCTION(VertexAttrib4Nbv);
        GLFL_LOAD_FUNCTION(VertexAttrib4Niv);
        GLFL_LOAD_FUNCTION(VertexAttrib4Nsv);
        GLFL_LOAD_FUNCTION(VertexAttrib4Nub);
        GLFL_LOAD_FUNCTION(VertexAttrib4Nubv);
        GLFL_LOAD_FUNCTION(VertexAttrib4Nuiv);
        GLFL_LOAD_FUNCTION(VertexAttrib4Nusv);
        GLFL_LOAD_FUNCTION(VertexAttrib4bv);
        GLFL_LOAD_FUNCTION(VertexAttrib4d);
        GLFL_LOAD_FUNCTION(VertexAttrib4dv);
        GLFL_LOAD_FUNCTION(VertexAttrib4f);
        GLFL_LOAD_FUNCTION(VertexAttrib4fv);
        GLFL_LOAD_FUNCTION(VertexAttrib4iv);
        GLFL_LOAD_FUNCTION(VertexAttrib4s);
        GLFL_LOAD_FUNCTION(VertexAttrib4sv);
        GLFL_LOAD_FUNCTION(VertexAttrib4ubv);
        GLFL_LOAD_FUNCTION(VertexAttrib4uiv);
        GLFL_LOAD_FUNCTION(VertexAttrib4usv);
        GLFL_LOAD_FUNCTION(VertexAttribPointer);
      case 0x10000 * 1 + 5:
        GLFL_LOAD_FUNCTION(GenQueries);
        GLFL_LOAD_FUNCTION(DeleteQueries);
        GLFL_LOAD_FUNCTION(IsQuery);
        GLFL_LOAD_FUNCTION(BeginQuery);
        GLFL_LOAD_FUNCTION(EndQuery);
        GLFL_LOAD_FUNCTION(GetQueryiv);
        GLFL_LOAD_FUNCTION(GetQueryObjectiv);
        GLFL_LOAD_FUNCTION(GetQueryObjectuiv);
        GLFL_LOAD_FUNCTION(BindBuffer);
        GLFL_LOAD_FUNCTION(DeleteBuffers);
        GLFL_LOAD_FUNCTION(GenBuffers);
        GLFL_LOAD_FUNCTION(IsBuffer);
        GLFL_LOAD_FUNCTION(BufferData);
        GLFL_LOAD_FUNCTION(BufferSubData);
        GLFL_LOAD_FUNCTION(GetBufferSubData);
        GLFL_LOAD_FUNCTION(MapBuffer);
        GLFL_LOAD_FUNCTION(UnmapBuffer);
        GLFL_LOAD_FUNCTION(GetBufferParameteriv);
        GLFL_LOAD_FUNCTION(GetBufferPointerv);
      case 0x10000 * 1 + 4:
        GLFL_LOAD_FUNCTION(BlendFuncSeparate);
        GLFL_LOAD_FUNCTION(MultiDrawArrays);
        GLFL_LOAD_FUNCTION(MultiDrawElements);
        GLFL_LOAD_FUNCTION(PointParameterf);
        GLFL_LOAD_FUNCTION(PointParameterfv);
        GLFL_LOAD_FUNCTION(PointParameteri);
        GLFL_LOAD_FUNCTION(PointParameteriv);
        GLFL_LOAD_FUNCTION(FogCoordf);
        GLFL_LOAD_FUNCTION(FogCoordfv);
        GLFL_LOAD_FUNCTION(FogCoordd);
        GLFL_LOAD_FUNCTION(FogCoorddv);
        GLFL_LOAD_FUNCTION(FogCoordPointer);
        GLFL_LOAD_FUNCTION(SecondaryColor3b);
        GLFL_LOAD_FUNCTION(SecondaryColor3bv);
        GLFL_LOAD_FUNCTION(SecondaryColor3d);
        GLFL_LOAD_FUNCTION(SecondaryColor3dv);
        GLFL_LOAD_FUNCTION(SecondaryColor3f);
        GLFL_LOAD_FUNCTION(SecondaryColor3fv);
        GLFL_LOAD_FUNCTION(SecondaryColor3i);
        GLFL_LOAD_FUNCTION(SecondaryColor3iv);
        GLFL_LOAD_FUNCTION(SecondaryColor3s);
        GLFL_LOAD_FUNCTION(SecondaryColor3sv);
        GLFL_LOAD_FUNCTION(SecondaryColor3ub);
        GLFL_LOAD_FUNCTION(SecondaryColor3ubv);
        GLFL_LOAD_FUNCTION(SecondaryColor3ui);
        GLFL_LOAD_FUNCTION(SecondaryColor3uiv);
        GLFL_LOAD_FUNCTION(SecondaryColor3us);
        GLFL_LOAD_FUNCTION(SecondaryColor3usv);
        GLFL_LOAD_FUNCTION(SecondaryColorPointer);
        GLFL_LOAD_FUNCTION(WindowPos2d);
        GLFL_LOAD_FUNCTION(WindowPos2dv);
        GLFL_LOAD_FUNCTION(WindowPos2f);
        GLFL_LOAD_FUNCTION(WindowPos2fv);
        GLFL_LOAD_FUNCTION(WindowPos2i);
        GLFL_LOAD_FUNCTION(WindowPos2iv);
        GLFL_LOAD_FUNCTION(WindowPos2s);
        GLFL_LOAD_FUNCTION(WindowPos2sv);
        GLFL_LOAD_FUNCTION(WindowPos3d);
        GLFL_LOAD_FUNCTION(WindowPos3dv);
        GLFL_LOAD_FUNCTION(WindowPos3f);
        GLFL_LOAD_FUNCTION(WindowPos3fv);
        GLFL_LOAD_FUNCTION(WindowPos3i);
        GLFL_LOAD_FUNCTION(WindowPos3iv);
        GLFL_LOAD_FUNCTION(WindowPos3s);
        GLFL_LOAD_FUNCTION(WindowPos3sv);
        GLFL_LOAD_FUNCTION(BlendColor);
        GLFL_LOAD_FUNCTION(BlendEquation);
      case 0x10000 * 1 + 3:
        GLFL_LOAD_FUNCTION(ActiveTexture);
        GLFL_LOAD_FUNCTION(SampleCoverage);
        GLFL_LOAD_FUNCTION(CompressedTexImage3D);
        GLFL_LOAD_FUNCTION(CompressedTexImage2D);
        GLFL_LOAD_FUNCTION(CompressedTexImage1D);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage3D);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage2D);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage1D);
        GLFL_LOAD_FUNCTION(GetCompressedTexImage);
        GLFL_LOAD_FUNCTION(ClientActiveTexture);
        GLFL_LOAD_FUNCTION(MultiTexCoord1d);
        GLFL_LOAD_FUNCTION(MultiTexCoord1dv);
        GLFL_LOAD_FUNCTION(MultiTexCoord1f);
        GLFL_LOAD_FUNCTION(MultiTexCoord1fv);
        GLFL_LOAD_FUNCTION(MultiTexCoord1i);
        GLFL_LOAD_FUNCTION(MultiTexCoord1iv);
        GLFL_LOAD_FUNCTION(MultiTexCoord1s);
        GLFL_LOAD_FUNCTION(MultiTexCoord1sv);
        GLFL_LOAD_FUNCTION(MultiTexCoord2d);
        GLFL_LOAD_FUNCTION(MultiTexCoord2dv);
        GLFL_LOAD_FUNCTION(MultiTexCoord2f);
        GLFL_LOAD_FUNCTION(MultiTexCoord2fv);
        GLFL_LOAD_FUNCTION(MultiTexCoord2i);
        GLFL_LOAD_FUNCTION(MultiTexCoord2iv);
        GLFL_LOAD_FUNCTION(MultiTexCoord2s);
        GLFL_LOAD_FUNCTION(MultiTexCoord2sv);
        GLFL_LOAD_FUNCTION(MultiTexCoord3d);
        GLFL_LOAD_FUNCTION(MultiTexCoord3dv);
        GLFL_LOAD_FUNCTION(MultiTexCoord3f);
        GLFL_LOAD_FUNCTION(MultiTexCoord3fv);
        GLFL_LOAD_FUNCTION(MultiTexCoord3i);
        GLFL_LOAD_FUNCTION(MultiTexCoord3iv);
        GLFL_LOAD_FUNCTION(MultiTexCoord3s);
        GLFL_LOAD_FUNCTION(MultiTexCoord3sv);
        GLFL_LOAD_FUNCTION(MultiTexCoord4d);
        GLFL_LOAD_FUNCTION(MultiTexCoord4dv);
        GLFL_LOAD_FUNCTION(MultiTexCoord4f);
        GLFL_LOAD_FUNCTION(MultiTexCoord4fv);
        GLFL_LOAD_FUNCTION(MultiTexCoord4i);
        GLFL_LOAD_FUNCTION(MultiTexCoord4iv);
        GLFL_LOAD_FUNCTION(MultiTexCoord4s);
        GLFL_LOAD_FUNCTION(MultiTexCoord4sv);
        GLFL_LOAD_FUNCTION(LoadTransposeMatrixf);
        GLFL_LOAD_FUNCTION(LoadTransposeMatrixd);
        GLFL_LOAD_FUNCTION(MultTransposeMatrixf);
        GLFL_LOAD_FUNCTION(MultTransposeMatrixd);
      case 0x10000 * 1 + 2:
        GLFL_LOAD_FUNCTION(DrawRangeElements);
        GLFL_LOAD_FUNCTION(TexImage3D);
        GLFL_LOAD_FUNCTION(TexSubImage3D);
        GLFL_LOAD_FUNCTION(CopyTexSubImage3D);
      case 0x10000 * 1 + 1:
        GLFL_LOAD_FUNCTION(DrawArrays);
        GLFL_LOAD_FUNCTION(DrawElements);
        GLFL_LOAD_FUNCTION(GetPointerv);
        GLFL_LOAD_FUNCTION(PolygonOffset);
        GLFL_LOAD_FUNCTION(CopyTexImage1D);
        GLFL_LOAD_FUNCTION(CopyTexImage2D);
        GLFL_LOAD_FUNCTION(CopyTexSubImage1D);
        GLFL_LOAD_FUNCTION(CopyTexSubImage2D);
        GLFL_LOAD_FUNCTION(TexSubImage1D);
        GLFL_LOAD_FUNCTION(TexSubImage2D);
        GLFL_LOAD_FUNCTION(BindTexture);
        GLFL_LOAD_FUNCTION(DeleteTextures);
        GLFL_LOAD_FUNCTION(GenTextures);
        GLFL_LOAD_FUNCTION(IsTexture);
        GLFL_LOAD_FUNCTION(ArrayElement);
        GLFL_LOAD_FUNCTION(ColorPointer);
        GLFL_LOAD_FUNCTION(DisableClientState);
        GLFL_LOAD_FUNCTION(EdgeFlagPointer);
        GLFL_LOAD_FUNCTION(EnableClientState);
        GLFL_LOAD_FUNCTION(IndexPointer);
        GLFL_LOAD_FUNCTION(InterleavedArrays);
        GLFL_LOAD_FUNCTION(NormalPointer);
        GLFL_LOAD_FUNCTION(TexCoordPointer);
        GLFL_LOAD_FUNCTION(VertexPointer);
        GLFL_LOAD_FUNCTION(AreTexturesResident);
        GLFL_LOAD_FUNCTION(PrioritizeTextures);
        GLFL_LOAD_FUNCTION(Indexub);
        GLFL_LOAD_FUNCTION(Indexubv);
        GLFL_LOAD_FUNCTION(PopClientAttrib);
        GLFL_LOAD_FUNCTION(PushClientAttrib);
      case 0x10000 * 1 + 0:
        GLFL_LOAD_FUNCTION(CullFace);
        GLFL_LOAD_FUNCTION(FrontFace);
        GLFL_LOAD_FUNCTION(Hint);
        GLFL_LOAD_FUNCTION(LineWidth);
        GLFL_LOAD_FUNCTION(PointSize);
        GLFL_LOAD_FUNCTION(PolygonMode);
        GLFL_LOAD_FUNCTION(Scissor);
        GLFL_LOAD_FUNCTION(TexParameterf);
        GLFL_LOAD_FUNCTION(TexParameterfv);
        GLFL_LOAD_FUNCTION(TexParameteri);
        GLFL_LOAD_FUNCTION(TexParameteriv);
        GLFL_LOAD_FUNCTION(TexImage1D);
        GLFL_LOAD_FUNCTION(TexImage2D);
        GLFL_LOAD_FUNCTION(DrawBuffer);
        GLFL_LOAD_FUNCTION(Clear);
        GLFL_LOAD_FUNCTION(ClearColor);
        GLFL_LOAD_FUNCTION(ClearStencil);
        GLFL_LOAD_FUNCTION(ClearDepth);
        GLFL_LOAD_FUNCTION(StencilMask);
        GLFL_LOAD_FUNCTION(ColorMask);
        GLFL_LOAD_FUNCTION(DepthMask);
        GLFL_LOAD_FUNCTION(Disable);
        GLFL_LOAD_FUNCTION(Enable);
        GLFL_LOAD_FUNCTION(Finish);
        GLFL_LOAD_FUNCTION(Flush);
        GLFL_LOAD_FUNCTION(BlendFunc);
        GLFL_LOAD_FUNCTION(LogicOp);
        GLFL_LOAD_FUNCTION(StencilFunc);
        GLFL_LOAD_FUNCTION(StencilOp);
        GLFL_LOAD_FUNCTION(DepthFunc);
        GLFL_LOAD_FUNCTION(PixelStoref);
        GLFL_LOAD_FUNCTION(PixelStorei);
        GLFL_LOAD_FUNCTION(ReadBuffer);
        GLFL_LOAD_FUNCTION(ReadPixels);
        GLFL_LOAD_FUNCTION(GetBooleanv);
        GLFL_LOAD_FUNCTION(GetDoublev);
        GLFL_LOAD_FUNCTION(GetError);
        GLFL_LOAD_FUNCTION(GetFloatv);
        GLFL_LOAD_FUNCTION(GetIntegerv);
        GLFL_LOAD_FUNCTION(GetString);
        GLFL_LOAD_FUNCTION(GetTexImage);
        GLFL_LOAD_FUNCTION(GetTexParameterfv);
        GLFL_LOAD_FUNCTION(GetTexParameteriv);
        GLFL_LOAD_FUNCTION(GetTexLevelParameterfv);
        GLFL_LOAD_FUNCTION(GetTexLevelParameteriv);
        GLFL_LOAD_FUNCTION(IsEnabled);
        GLFL_LOAD_FUNCTION(DepthRange);
        GLFL_LOAD_FUNCTION(Viewport);
        GLFL_LOAD_FUNCTION(NewList);
        GLFL_LOAD_FUNCTION(EndList);
        GLFL_LOAD_FUNCTION(CallList);
        GLFL_LOAD_FUNCTION(CallLists);
        GLFL_LOAD_FUNCTION(DeleteLists);
        GLFL_LOAD_FUNCTION(GenLists);
        GLFL_LOAD_FUNCTION(ListBase);
        GLFL_LOAD_FUNCTION(Begin);
        GLFL_LOAD_FUNCTION(Bitmap);
        GLFL_LOAD_FUNCTION(Color3b);
        GLFL_LOAD_FUNCTION(Color3bv);
        GLFL_LOAD_FUNCTION(Color3d);
        GLFL_LOAD_FUNCTION(Color3dv);
        GLFL_LOAD_FUNCTION(Color3f);
        GLFL_LOAD_FUNCTION(Color3fv);
        GLFL_LOAD_FUNCTION(Color3i);
        GLFL_LOAD_FUNCTION(Color3iv);
        GLFL_LOAD_FUNCTION(Color3s);
        GLFL_LOAD_FUNCTION(Color3sv);
        GLFL_LOAD_FUNCTION(Color3ub);
        GLFL_LOAD_FUNCTION(Color3ubv);
        GLFL_LOAD_FUNCTION(Color3ui);
        GLFL_LOAD_FUNCTION(Color3uiv);
        GLFL_LOAD_FUNCTION(Color3us);
        GLFL_LOAD_FUNCTION(Color3usv);
        GLFL_LOAD_FUNCTION(Color4b);
        GLFL_LOAD_FUNCTION(Color4bv);
        GLFL_LOAD_FUNCTION(Color4d);
        GLFL_LOAD_FUNCTION(Color4dv);
        GLFL_LOAD_FUNCTION(Color4f);
        GLFL_LOAD_FUNCTION(Color4fv);
        GLFL_LOAD_FUNCTION(Color4i);
        GLFL_LOAD_FUNCTION(Color4iv);
        GLFL_LOAD_FUNCTION(Color4s);
        GLFL_LOAD_FUNCTION(Color4sv);
        GLFL_LOAD_FUNCTION(Color4ub);
        GLFL_LOAD_FUNCTION(Color4ubv);
        GLFL_LOAD_FUNCTION(Color4ui);
        GLFL_LOAD_FUNCTION(Color4uiv);
        GLFL_LOAD_FUNCTION(Color4us);
        GLFL_LOAD_FUNCTION(Color4usv);
        GLFL_LOAD_FUNCTION(EdgeFlag);
        GLFL_LOAD_FUNCTION(EdgeFlagv);
        GLFL_LOAD_FUNCTION(End);
        GLFL_LOAD_FUNCTION(Indexd);
        GLFL_LOAD_FUNCTION(Indexdv);
        GLFL_LOAD_FUNCTION(Indexf);
        GLFL_LOAD_FUNCTION(Indexfv);
        GLFL_LOAD_FUNCTION(Indexi);
        GLFL_LOAD_FUNCTION(Indexiv);
        GLFL_LOAD_FUNCTION(Indexs);
        GLFL_LOAD_FUNCTION(Indexsv);
        GLFL_LOAD_FUNCTION(Normal3b);
        GLFL_LOAD_FUNCTION(Normal3bv);
        GLFL_LOAD_FUNCTION(Normal3d);
        GLFL_LOAD_FUNCTION(Normal3dv);
        GLFL_LOAD_FUNCTION(Normal3f);
        GLFL_LOAD_FUNCTION(Normal3fv);
        GLFL_LOAD_FUNCTION(Normal3i);
        GLFL_LOAD_FUNCTION(Normal3iv);
        GLFL_LOAD_FUNCTION(Normal3s);
        GLFL_LOAD_FUNCTION(Normal3sv);
        GLFL_LOAD_FUNCTION(RasterPos2d);
        GLFL_LOAD_FUNCTION(RasterPos2dv);
        GLFL_LOAD_FUNCTION(RasterPos2f);
        GLFL_LOAD_FUNCTION(RasterPos2fv);
        GLFL_LOAD_FUNCTION(RasterPos2i);
        GLFL_LOAD_FUNCTION(RasterPos2iv);
        GLFL_LOAD_FUNCTION(RasterPos2s);
        GLFL_LOAD_FUNCTION(RasterPos2sv);
        GLFL_LOAD_FUNCTION(RasterPos3d);
        GLFL_LOAD_FUNCTION(RasterPos3dv);
        GLFL_LOAD_FUNCTION(RasterPos3f);
        GLFL_LOAD_FUNCTION(RasterPos3fv);
        GLFL_LOAD_FUNCTION(RasterPos3i);
        GLFL_LOAD_FUNCTION(RasterPos3iv);
        GLFL_LOAD_FUNCTION(RasterPos3s);
        GLFL_LOAD_FUNCTION(RasterPos3sv);
        GLFL_LOAD_FUNCTION(RasterPos4d);
        GLFL_LOAD_FUNCTION(RasterPos4dv);
        GLFL_LOAD_FUNCTION(RasterPos4f);
        GLFL_LOAD_FUNCTION(RasterPos4fv);
        GLFL_LOAD_FUNCTION(RasterPos4i);
        GLFL_LOAD_FUNCTION(RasterPos4iv);
        GLFL_LOAD_FUNCTION(RasterPos4s);
        GLFL_LOAD_FUNCTION(RasterPos4sv);
        GLFL_LOAD_FUNCTION(Rectd);
        GLFL_LOAD_FUNCTION(Rectdv);
        GLFL_LOAD_FUNCTION(Rectf);
        GLFL_LOAD_FUNCTION(Rectfv);
        GLFL_LOAD_FUNCTION(Recti);
        GLFL_LOAD_FUNCTION(Rectiv);
        GLFL_LOAD_FUNCTION(Rects);
        GLFL_LOAD_FUNCTION(Rectsv);
        GLFL_LOAD_FUNCTION(TexCoord1d);
        GLFL_LOAD_FUNCTION(TexCoord1dv);
        GLFL_LOAD_FUNCTION(TexCoord1f);
        GLFL_LOAD_FUNCTION(TexCoord1fv);
        GLFL_LOAD_FUNCTION(TexCoord1i);
        GLFL_LOAD_FUNCTION(TexCoord1iv);
        GLFL_LOAD_FUNCTION(TexCoord1s);
        GLFL_LOAD_FUNCTION(TexCoord1sv);
        GLFL_LOAD_FUNCTION(TexCoord2d);
        GLFL_LOAD_FUNCTION(TexCoord2dv);
        GLFL_LOAD_FUNCTION(TexCoord2f);
        GLFL_LOAD_FUNCTION(TexCoord2fv);
        GLFL_LOAD_FUNCTION(TexCoord2i);
        GLFL_LOAD_FUNCTION(TexCoord2iv);
        GLFL_LOAD_FUNCTION(TexCoord2s);
        GLFL_LOAD_FUNCTION(TexCoord2sv);
        GLFL_LOAD_FUNCTION(TexCoord3d);
        GLFL_LOAD_FUNCTION(TexCoord3dv);
        GLFL_LOAD_FUNCTION(TexCoord3f);
        GLFL_LOAD_FUNCTION(TexCoord3fv);
        GLFL_LOAD_FUNCTION(TexCoord3i);
        GLFL_LOAD_FUNCTION(TexCoord3iv);
        GLFL_LOAD_FUNCTION(TexCoord3s);
        GLFL_LOAD_FUNCTION(TexCoord3sv);
        GLFL_LOAD_FUNCTION(TexCoord4d);
        GLFL_LOAD_FUNCTION(TexCoord4dv);
        GLFL_LOAD_FUNCTION(TexCoord4f);
        GLFL_LOAD_FUNCTION(TexCoord4fv);
        GLFL_LOAD_FUNCTION(TexCoord4i);
        GLFL_LOAD_FUNCTION(TexCoord4iv);
        GLFL_LOAD_FUNCTION(TexCoord4s);
        GLFL_LOAD_FUNCTION(TexCoord4sv);
        GLFL_LOAD_FUNCTION(Vertex2d);
        GLFL_LOAD_FUNCTION(Vertex2dv);
        GLFL_LOAD_FUNCTION(Vertex2f);
        GLFL_LOAD_FUNCTION(Vertex2fv);
        GLFL_LOAD_FUNCTION(Vertex2i);
        GLFL_LOAD_FUNCTION(Vertex2iv);
        GLFL_LOAD_FUNCTION(Vertex2s);
        GLFL_LOAD_FUNCTION(Vertex2sv);
        GLFL_LOAD_FUNCTION(Vertex3d);
        GLFL_LOAD_FUNCTION(Vertex3dv);
        GLFL_LOAD_FUNCTION(Vertex3f);
        GLFL_LOAD_FUNCTION(Vertex3fv);
        GLFL_LOAD_FUNCTION(Vertex3i);
        GLFL_LOAD_FUNCTION(Vertex3iv);
        GLFL_LOAD_FUNCTION(Vertex3s);
        GLFL_LOAD_FUNCTION(Vertex3sv);
        GLFL_LOAD_FUNCTION(Vertex4d);
        GLFL_LOAD_FUNCTION(Vertex4dv);
        GLFL_LOAD_FUNCTION(Vertex4f);
        GLFL_LOAD_FUNCTION(Vertex4fv);
        GLFL_LOAD_FUNCTION(Vertex4i);
        GLFL_LOAD_FUNCTION(Vertex4iv);
        GLFL_LOAD_FUNCTION(Vertex4s);
        GLFL_LOAD_FUNCTION(Vertex4sv);
        GLFL_LOAD_FUNCTION(ClipPlane);
        GLFL_LOAD_FUNCTION(ColorMaterial);
        GLFL_LOAD_FUNCTION(Fogf);
        GLFL_LOAD_FUNCTION(Fogfv);
        GLFL_LOAD_FUNCTION(Fogi);
        GLFL_LOAD_FUNCTION(Fogiv);
        GLFL_LOAD_FUNCTION(Lightf);
        GLFL_LOAD_FUNCTION(Lightfv);
        GLFL_LOAD_FUNCTION(Lighti);
        GLFL_LOAD_FUNCTION(Lightiv);
        GLFL_LOAD_FUNCTION(LightModelf);
        GLFL_LOAD_FUNCTION(LightModelfv);
        GLFL_LOAD_FUNCTION(LightModeli);
        GLFL_LOAD_FUNCTION(LightModeliv);
        GLFL_LOAD_FUNCTION(LineStipple);
        GLFL_LOAD_FUNCTION(Materialf);
        GLFL_LOAD_FUNCTION(Materialfv);
        GLFL_LOAD_FUNCTION(Materiali);
        GLFL_LOAD_FUNCTION(Materialiv);
        GLFL_LOAD_FUNCTION(PolygonStipple);
        GLFL_LOAD_FUNCTION(ShadeModel);
        GLFL_LOAD_FUNCTION(TexEnvf);
        GLFL_LOAD_FUNCTION(TexEnvfv);
        GLFL_LOAD_FUNCTION(TexEnvi);
        GLFL_LOAD_FUNCTION(TexEnviv);
        GLFL_LOAD_FUNCTION(TexGend);
        GLFL_LOAD_FUNCTION(TexGendv);
        GLFL_LOAD_FUNCTION(TexGenf);
        GLFL_LOAD_FUNCTION(TexGenfv);
        GLFL_LOAD_FUNCTION(TexGeni);
        GLFL_LOAD_FUNCTION(TexGeniv);
        GLFL_LOAD_FUNCTION(FeedbackBuffer);
        GLFL_LOAD_FUNCTION(SelectBuffer);
        GLFL_LOAD_FUNCTION(RenderMode);
        GLFL_LOAD_FUNCTION(InitNames);
        GLFL_LOAD_FUNCTION(LoadName);
        GLFL_LOAD_FUNCTION(PassThrough);
        GLFL_LOAD_FUNCTION(PopName);
        GLFL_LOAD_FUNCTION(PushName);
        GLFL_LOAD_FUNCTION(ClearAccum);
        GLFL_LOAD_FUNCTION(ClearIndex);
        GLFL_LOAD_FUNCTION(IndexMask);
        GLFL_LOAD_FUNCTION(Accum);
        GLFL_LOAD_FUNCTION(PopAttrib);
        GLFL_LOAD_FUNCTION(PushAttrib);
        GLFL_LOAD_FUNCTION(Map1d);
        GLFL_LOAD_FUNCTION(Map1f);
        GLFL_LOAD_FUNCTION(Map2d);
        GLFL_LOAD_FUNCTION(Map2f);
        GLFL_LOAD_FUNCTION(MapGrid1d);
        GLFL_LOAD_FUNCTION(MapGrid1f);
        GLFL_LOAD_FUNCTION(MapGrid2d);
        GLFL_LOAD_FUNCTION(MapGrid2f);
        GLFL_LOAD_FUNCTION(EvalCoord1d);
        GLFL_LOAD_FUNCTION(EvalCoord1dv);
        GLFL_LOAD_FUNCTION(EvalCoord1f);
        GLFL_LOAD_FUNCTION(EvalCoord1fv);
        GLFL_LOAD_FUNCTION(EvalCoord2d);
        GLFL_LOAD_FUNCTION(EvalCoord2dv);
        GLFL_LOAD_FUNCTION(EvalCoord2f);
        GLFL_LOAD_FUNCTION(EvalCoord2fv);
        GLFL_LOAD_FUNCTION(EvalMesh1);
        GLFL_LOAD_FUNCTION(EvalPoint1);
        GLFL_LOAD_FUNCTION(EvalMesh2);
        GLFL_LOAD_FUNCTION(EvalPoint2);
        GLFL_LOAD_FUNCTION(AlphaFunc);
        GLFL_LOAD_FUNCTION(PixelZoom);
        GLFL_LOAD_FUNCTION(PixelTransferf);
        GLFL_LOAD_FUNCTION(PixelTransferi);
        GLFL_LOAD_FUNCTION(PixelMapfv);
        GLFL_LOAD_FUNCTION(PixelMapuiv);
        GLFL_LOAD_FUNCTION(PixelMapusv);
        GLFL_LOAD_FUNCTION(CopyPixels);
        GLFL_LOAD_FUNCTION(DrawPixels);
        GLFL_LOAD_FUNCTION(GetClipPlane);
        GLFL_LOAD_FUNCTION(GetLightfv);
        GLFL_LOAD_FUNCTION(GetLightiv);
        GLFL_LOAD_FUNCTION(GetMapdv);
        GLFL_LOAD_FUNCTION(GetMapfv);
        GLFL_LOAD_FUNCTION(GetMapiv);
        GLFL_LOAD_FUNCTION(GetMaterialfv);
        GLFL_LOAD_FUNCTION(GetMaterialiv);
        GLFL_LOAD_FUNCTION(GetPixelMapfv);
        GLFL_LOAD_FUNCTION(GetPixelMapuiv);
        GLFL_LOAD_FUNCTION(GetPixelMapusv);
        GLFL_LOAD_FUNCTION(GetPolygonStipple);
        GLFL_LOAD_FUNCTION(GetTexEnvfv);
        GLFL_LOAD_FUNCTION(GetTexEnviv);
        GLFL_LOAD_FUNCTION(GetTexGendv);
        GLFL_LOAD_FUNCTION(GetTexGenfv);
        GLFL_LOAD_FUNCTION(GetTexGeniv);
        GLFL_LOAD_FUNCTION(IsList);
        GLFL_LOAD_FUNCTION(Frustum);
        GLFL_LOAD_FUNCTION(LoadIdentity);
        GLFL_LOAD_FUNCTION(LoadMatrixf);
        GLFL_LOAD_FUNCTION(LoadMatrixd);
        GLFL_LOAD_FUNCTION(MatrixMode);
        GLFL_LOAD_FUNCTION(MultMatrixf);
        GLFL_LOAD_FUNCTION(MultMatrixd);
        GLFL_LOAD_FUNCTION(Ortho);
        GLFL_LOAD_FUNCTION(PopMatrix);
        GLFL_LOAD_FUNCTION(PushMatrix);
        GLFL_LOAD_FUNCTION(Rotated);
        GLFL_LOAD_FUNCTION(Rotatef);
        GLFL_LOAD_FUNCTION(Scaled);
        GLFL_LOAD_FUNCTION(Scalef);
        GLFL_LOAD_FUNCTION(Translated);
        GLFL_LOAD_FUNCTION(Translatef);
    }
}
static void load_version_gles1(int major, int minor)
{
    switch (0x10000 * major + minor)
    {
      default:
      case 0x10000 * 1 + 0:
        GLFL_LOAD_FUNCTION(AlphaFunc);
        GLFL_LOAD_FUNCTION(ClearColor);
        GLFL_LOAD_FUNCTION(ClearDepthf);
        GLFL_LOAD_FUNCTION(ClipPlanef);
        GLFL_LOAD_FUNCTION(Color4f);
        GLFL_LOAD_FUNCTION(DepthRangef);
        GLFL_LOAD_FUNCTION(Fogf);
        GLFL_LOAD_FUNCTION(Fogfv);
        GLFL_LOAD_FUNCTION(Frustumf);
        GLFL_LOAD_FUNCTION(GetClipPlanef);
        GLFL_LOAD_FUNCTION(GetFloatv);
        GLFL_LOAD_FUNCTION(GetLightfv);
        GLFL_LOAD_FUNCTION(GetMaterialfv);
        GLFL_LOAD_FUNCTION(GetTexEnvfv);
        GLFL_LOAD_FUNCTION(GetTexParameterfv);
        GLFL_LOAD_FUNCTION(LightModelf);
        GLFL_LOAD_FUNCTION(LightModelfv);
        GLFL_LOAD_FUNCTION(Lightf);
        GLFL_LOAD_FUNCTION(Lightfv);
        GLFL_LOAD_FUNCTION(LineWidth);
        GLFL_LOAD_FUNCTION(LoadMatrixf);
        GLFL_LOAD_FUNCTION(Materialf);
        GLFL_LOAD_FUNCTION(Materialfv);
        GLFL_LOAD_FUNCTION(MultMatrixf);
        GLFL_LOAD_FUNCTION(MultiTexCoord4f);
        GLFL_LOAD_FUNCTION(Normal3f);
        GLFL_LOAD_FUNCTION(Orthof);
        GLFL_LOAD_FUNCTION(PointParameterf);
        GLFL_LOAD_FUNCTION(PointParameterfv);
        GLFL_LOAD_FUNCTION(PointSize);
        GLFL_LOAD_FUNCTION(PolygonOffset);
        GLFL_LOAD_FUNCTION(Rotatef);
        GLFL_LOAD_FUNCTION(Scalef);
        GLFL_LOAD_FUNCTION(TexEnvf);
        GLFL_LOAD_FUNCTION(TexEnvfv);
        GLFL_LOAD_FUNCTION(TexParameterf);
        GLFL_LOAD_FUNCTION(TexParameterfv);
        GLFL_LOAD_FUNCTION(Translatef);
        GLFL_LOAD_FUNCTION(ActiveTexture);
        GLFL_LOAD_FUNCTION(AlphaFuncx);
        GLFL_LOAD_FUNCTION(BindBuffer);
        GLFL_LOAD_FUNCTION(BindTexture);
        GLFL_LOAD_FUNCTION(BlendFunc);
        GLFL_LOAD_FUNCTION(BufferData);
        GLFL_LOAD_FUNCTION(BufferSubData);
        GLFL_LOAD_FUNCTION(Clear);
        GLFL_LOAD_FUNCTION(ClearColorx);
        GLFL_LOAD_FUNCTION(ClearDepthx);
        GLFL_LOAD_FUNCTION(ClearStencil);
        GLFL_LOAD_FUNCTION(ClientActiveTexture);
        GLFL_LOAD_FUNCTION(ClipPlanex);
        GLFL_LOAD_FUNCTION(Color4ub);
        GLFL_LOAD_FUNCTION(Color4x);
        GLFL_LOAD_FUNCTION(ColorMask);
        GLFL_LOAD_FUNCTION(ColorPointer);
        GLFL_LOAD_FUNCTION(CompressedTexImage2D);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage2D);
        GLFL_LOAD_FUNCTION(CopyTexImage2D);
        GLFL_LOAD_FUNCTION(CopyTexSubImage2D);
        GLFL_LOAD_FUNCTION(CullFace);
        GLFL_LOAD_FUNCTION(DeleteBuffers);
        GLFL_LOAD_FUNCTION(DeleteTextures);
        GLFL_LOAD_FUNCTION(DepthFunc);
        GLFL_LOAD_FUNCTION(DepthMask);
        GLFL_LOAD_FUNCTION(DepthRangex);
        GLFL_LOAD_FUNCTION(Disable);
        GLFL_LOAD_FUNCTION(DisableClientState);
        GLFL_LOAD_FUNCTION(DrawArrays);
        GLFL_LOAD_FUNCTION(DrawElements);
        GLFL_LOAD_FUNCTION(Enable);
        GLFL_LOAD_FUNCTION(EnableClientState);
        GLFL_LOAD_FUNCTION(Finish);
        GLFL_LOAD_FUNCTION(Flush);
        GLFL_LOAD_FUNCTION(Fogx);
        GLFL_LOAD_FUNCTION(Fogxv);
        GLFL_LOAD_FUNCTION(FrontFace);
        GLFL_LOAD_FUNCTION(Frustumx);
        GLFL_LOAD_FUNCTION(GetBooleanv);
        GLFL_LOAD_FUNCTION(GetBufferParameteriv);
        GLFL_LOAD_FUNCTION(GetClipPlanex);
        GLFL_LOAD_FUNCTION(GenBuffers);
        GLFL_LOAD_FUNCTION(GenTextures);
        GLFL_LOAD_FUNCTION(GetError);
        GLFL_LOAD_FUNCTION(GetFixedv);
        GLFL_LOAD_FUNCTION(GetIntegerv);
        GLFL_LOAD_FUNCTION(GetLightxv);
        GLFL_LOAD_FUNCTION(GetMaterialxv);
        GLFL_LOAD_FUNCTION(GetPointerv);
        GLFL_LOAD_FUNCTION(GetString);
        GLFL_LOAD_FUNCTION(GetTexEnviv);
        GLFL_LOAD_FUNCTION(GetTexEnvxv);
        GLFL_LOAD_FUNCTION(GetTexParameteriv);
        GLFL_LOAD_FUNCTION(GetTexParameterxv);
        GLFL_LOAD_FUNCTION(Hint);
        GLFL_LOAD_FUNCTION(IsBuffer);
        GLFL_LOAD_FUNCTION(IsEnabled);
        GLFL_LOAD_FUNCTION(IsTexture);
        GLFL_LOAD_FUNCTION(LightModelx);
        GLFL_LOAD_FUNCTION(LightModelxv);
        GLFL_LOAD_FUNCTION(Lightx);
        GLFL_LOAD_FUNCTION(Lightxv);
        GLFL_LOAD_FUNCTION(LineWidthx);
        GLFL_LOAD_FUNCTION(LoadIdentity);
        GLFL_LOAD_FUNCTION(LoadMatrixx);
        GLFL_LOAD_FUNCTION(LogicOp);
        GLFL_LOAD_FUNCTION(Materialx);
        GLFL_LOAD_FUNCTION(Materialxv);
        GLFL_LOAD_FUNCTION(MatrixMode);
        GLFL_LOAD_FUNCTION(MultMatrixx);
        GLFL_LOAD_FUNCTION(MultiTexCoord4x);
        GLFL_LOAD_FUNCTION(Normal3x);
        GLFL_LOAD_FUNCTION(NormalPointer);
        GLFL_LOAD_FUNCTION(Orthox);
        GLFL_LOAD_FUNCTION(PixelStorei);
        GLFL_LOAD_FUNCTION(PointParameterx);
        GLFL_LOAD_FUNCTION(PointParameterxv);
        GLFL_LOAD_FUNCTION(PointSizex);
        GLFL_LOAD_FUNCTION(PolygonOffsetx);
        GLFL_LOAD_FUNCTION(PopMatrix);
        GLFL_LOAD_FUNCTION(PushMatrix);
        GLFL_LOAD_FUNCTION(ReadPixels);
        GLFL_LOAD_FUNCTION(Rotatex);
        GLFL_LOAD_FUNCTION(SampleCoverage);
        GLFL_LOAD_FUNCTION(SampleCoveragex);
        GLFL_LOAD_FUNCTION(Scalex);
        GLFL_LOAD_FUNCTION(Scissor);
        GLFL_LOAD_FUNCTION(ShadeModel);
        GLFL_LOAD_FUNCTION(StencilFunc);
        GLFL_LOAD_FUNCTION(StencilMask);
        GLFL_LOAD_FUNCTION(StencilOp);
        GLFL_LOAD_FUNCTION(TexCoordPointer);
        GLFL_LOAD_FUNCTION(TexEnvi);
        GLFL_LOAD_FUNCTION(TexEnvx);
        GLFL_LOAD_FUNCTION(TexEnviv);
        GLFL_LOAD_FUNCTION(TexEnvxv);
        GLFL_LOAD_FUNCTION(TexImage2D);
        GLFL_LOAD_FUNCTION(TexParameteri);
        GLFL_LOAD_FUNCTION(TexParameterx);
        GLFL_LOAD_FUNCTION(TexParameteriv);
        GLFL_LOAD_FUNCTION(TexParameterxv);
        GLFL_LOAD_FUNCTION(TexSubImage2D);
        GLFL_LOAD_FUNCTION(Translatex);
        GLFL_LOAD_FUNCTION(VertexPointer);
        GLFL_LOAD_FUNCTION(Viewport);
    }
}
static void load_version_gles2(int major, int minor)
{
    switch (0x10000 * major + minor)
    {
      default:
      case 0x10000 * 3 + 2:
        GLFL_LOAD_FUNCTION(BlendBarrier);
        GLFL_LOAD_FUNCTION(CopyImageSubData);
        GLFL_LOAD_FUNCTION(DebugMessageControl);
        GLFL_LOAD_FUNCTION(DebugMessageInsert);
        GLFL_LOAD_FUNCTION(DebugMessageCallback);
        GLFL_LOAD_FUNCTION(GetDebugMessageLog);
        GLFL_LOAD_FUNCTION(PushDebugGroup);
        GLFL_LOAD_FUNCTION(PopDebugGroup);
        GLFL_LOAD_FUNCTION(ObjectLabel);
        GLFL_LOAD_FUNCTION(GetObjectLabel);
        GLFL_LOAD_FUNCTION(ObjectPtrLabel);
        GLFL_LOAD_FUNCTION(GetObjectPtrLabel);
        GLFL_LOAD_FUNCTION(GetPointerv);
        GLFL_LOAD_FUNCTION(Enablei);
        GLFL_LOAD_FUNCTION(Disablei);
        GLFL_LOAD_FUNCTION(BlendEquationi);
        GLFL_LOAD_FUNCTION(BlendEquationSeparatei);
        GLFL_LOAD_FUNCTION(BlendFunci);
        GLFL_LOAD_FUNCTION(BlendFuncSeparatei);
        GLFL_LOAD_FUNCTION(ColorMaski);
        GLFL_LOAD_FUNCTION(IsEnabledi);
        GLFL_LOAD_FUNCTION(DrawElementsBaseVertex);
        GLFL_LOAD_FUNCTION(DrawRangeElementsBaseVertex);
        GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertex);
        GLFL_LOAD_FUNCTION(FramebufferTexture);
        GLFL_LOAD_FUNCTION(PrimitiveBoundingBox);
        GLFL_LOAD_FUNCTION(GetGraphicsResetStatus);
        GLFL_LOAD_FUNCTION(ReadnPixels);
        GLFL_LOAD_FUNCTION(GetnUniformfv);
        GLFL_LOAD_FUNCTION(GetnUniformiv);
        GLFL_LOAD_FUNCTION(GetnUniformuiv);
        GLFL_LOAD_FUNCTION(MinSampleShading);
        GLFL_LOAD_FUNCTION(PatchParameteri);
        GLFL_LOAD_FUNCTION(TexParameterIiv);
        GLFL_LOAD_FUNCTION(TexParameterIuiv);
        GLFL_LOAD_FUNCTION(GetTexParameterIiv);
        GLFL_LOAD_FUNCTION(GetTexParameterIuiv);
        GLFL_LOAD_FUNCTION(SamplerParameterIiv);
        GLFL_LOAD_FUNCTION(SamplerParameterIuiv);
        GLFL_LOAD_FUNCTION(GetSamplerParameterIiv);
        GLFL_LOAD_FUNCTION(GetSamplerParameterIuiv);
        GLFL_LOAD_FUNCTION(TexBuffer);
        GLFL_LOAD_FUNCTION(TexBufferRange);
        GLFL_LOAD_FUNCTION(TexStorage3DMultisample);
      case 0x10000 * 3 + 1:
        GLFL_LOAD_FUNCTION(DispatchCompute);
        GLFL_LOAD_FUNCTION(DispatchComputeIndirect);
        GLFL_LOAD_FUNCTION(DrawArraysIndirect);
        GLFL_LOAD_FUNCTION(DrawElementsIndirect);
        GLFL_LOAD_FUNCTION(FramebufferParameteri);
        GLFL_LOAD_FUNCTION(GetFramebufferParameteriv);
        GLFL_LOAD_FUNCTION(GetProgramInterfaceiv);
        GLFL_LOAD_FUNCTION(GetProgramResourceIndex);
        GLFL_LOAD_FUNCTION(GetProgramResourceName);
        GLFL_LOAD_FUNCTION(GetProgramResourceiv);
        GLFL_LOAD_FUNCTION(GetProgramResourceLocation);
        GLFL_LOAD_FUNCTION(UseProgramStages);
        GLFL_LOAD_FUNCTION(ActiveShaderProgram);
        GLFL_LOAD_FUNCTION(CreateShaderProgramv);
        GLFL_LOAD_FUNCTION(BindProgramPipeline);
        GLFL_LOAD_FUNCTION(DeleteProgramPipelines);
        GLFL_LOAD_FUNCTION(GenProgramPipelines);
        GLFL_LOAD_FUNCTION(IsProgramPipeline);
        GLFL_LOAD_FUNCTION(GetProgramPipelineiv);
        GLFL_LOAD_FUNCTION(ProgramUniform1i);
        GLFL_LOAD_FUNCTION(ProgramUniform2i);
        GLFL_LOAD_FUNCTION(ProgramUniform3i);
        GLFL_LOAD_FUNCTION(ProgramUniform4i);
        GLFL_LOAD_FUNCTION(ProgramUniform1ui);
        GLFL_LOAD_FUNCTION(ProgramUniform2ui);
        GLFL_LOAD_FUNCTION(ProgramUniform3ui);
        GLFL_LOAD_FUNCTION(ProgramUniform4ui);
        GLFL_LOAD_FUNCTION(ProgramUniform1f);
        GLFL_LOAD_FUNCTION(ProgramUniform2f);
        GLFL_LOAD_FUNCTION(ProgramUniform3f);
        GLFL_LOAD_FUNCTION(ProgramUniform4f);
        GLFL_LOAD_FUNCTION(ProgramUniform1iv);
        GLFL_LOAD_FUNCTION(ProgramUniform2iv);
        GLFL_LOAD_FUNCTION(ProgramUniform3iv);
        GLFL_LOAD_FUNCTION(ProgramUniform4iv);
        GLFL_LOAD_FUNCTION(ProgramUniform1uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform2uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform3uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform4uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform1fv);
        GLFL_LOAD_FUNCTION(ProgramUniform2fv);
        GLFL_LOAD_FUNCTION(ProgramUniform3fv);
        GLFL_LOAD_FUNCTION(ProgramUniform4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3fv);
        GLFL_LOAD_FUNCTION(ValidateProgramPipeline);
        GLFL_LOAD_FUNCTION(GetProgramPipelineInfoLog);
        GLFL_LOAD_FUNCTION(BindImageTexture);
        GLFL_LOAD_FUNCTION(GetBooleani_v);
        GLFL_LOAD_FUNCTION(MemoryBarrier);
        GLFL_LOAD_FUNCTION(MemoryBarrierByRegion);
        GLFL_LOAD_FUNCTION(TexStorage2DMultisample);
        GLFL_LOAD_FUNCTION(GetMultisamplefv);
        GLFL_LOAD_FUNCTION(SampleMaski);
        GLFL_LOAD_FUNCTION(GetTexLevelParameteriv);
        GLFL_LOAD_FUNCTION(GetTexLevelParameterfv);
        GLFL_LOAD_FUNCTION(BindVertexBuffer);
        GLFL_LOAD_FUNCTION(VertexAttribFormat);
        GLFL_LOAD_FUNCTION(VertexAttribIFormat);
        GLFL_LOAD_FUNCTION(VertexAttribBinding);
        GLFL_LOAD_FUNCTION(VertexBindingDivisor);
      case 0x10000 * 3 + 0:
        GLFL_LOAD_FUNCTION(ReadBuffer);
        GLFL_LOAD_FUNCTION(DrawRangeElements);
        GLFL_LOAD_FUNCTION(TexImage3D);
        GLFL_LOAD_FUNCTION(TexSubImage3D);
        GLFL_LOAD_FUNCTION(CopyTexSubImage3D);
        GLFL_LOAD_FUNCTION(CompressedTexImage3D);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage3D);
        GLFL_LOAD_FUNCTION(GenQueries);
        GLFL_LOAD_FUNCTION(DeleteQueries);
        GLFL_LOAD_FUNCTION(IsQuery);
        GLFL_LOAD_FUNCTION(BeginQuery);
        GLFL_LOAD_FUNCTION(EndQuery);
        GLFL_LOAD_FUNCTION(GetQueryiv);
        GLFL_LOAD_FUNCTION(GetQueryObjectuiv);
        GLFL_LOAD_FUNCTION(UnmapBuffer);
        GLFL_LOAD_FUNCTION(GetBufferPointerv);
        GLFL_LOAD_FUNCTION(DrawBuffers);
        GLFL_LOAD_FUNCTION(UniformMatrix2x3fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3x2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix2x4fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4x2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3x4fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4x3fv);
        GLFL_LOAD_FUNCTION(BlitFramebuffer);
        GLFL_LOAD_FUNCTION(RenderbufferStorageMultisample);
        GLFL_LOAD_FUNCTION(FramebufferTextureLayer);
        GLFL_LOAD_FUNCTION(MapBufferRange);
        GLFL_LOAD_FUNCTION(FlushMappedBufferRange);
        GLFL_LOAD_FUNCTION(BindVertexArray);
        GLFL_LOAD_FUNCTION(DeleteVertexArrays);
        GLFL_LOAD_FUNCTION(GenVertexArrays);
        GLFL_LOAD_FUNCTION(IsVertexArray);
        GLFL_LOAD_FUNCTION(GetIntegeri_v);
        GLFL_LOAD_FUNCTION(BeginTransformFeedback);
        GLFL_LOAD_FUNCTION(EndTransformFeedback);
        GLFL_LOAD_FUNCTION(BindBufferRange);
        GLFL_LOAD_FUNCTION(BindBufferBase);
        GLFL_LOAD_FUNCTION(TransformFeedbackVaryings);
        GLFL_LOAD_FUNCTION(GetTransformFeedbackVarying);
        GLFL_LOAD_FUNCTION(VertexAttribIPointer);
        GLFL_LOAD_FUNCTION(GetVertexAttribIiv);
        GLFL_LOAD_FUNCTION(GetVertexAttribIuiv);
        GLFL_LOAD_FUNCTION(VertexAttribI4i);
        GLFL_LOAD_FUNCTION(VertexAttribI4ui);
        GLFL_LOAD_FUNCTION(VertexAttribI4iv);
        GLFL_LOAD_FUNCTION(VertexAttribI4uiv);
        GLFL_LOAD_FUNCTION(GetUniformuiv);
        GLFL_LOAD_FUNCTION(GetFragDataLocation);
        GLFL_LOAD_FUNCTION(Uniform1ui);
        GLFL_LOAD_FUNCTION(Uniform2ui);
        GLFL_LOAD_FUNCTION(Uniform3ui);
        GLFL_LOAD_FUNCTION(Uniform4ui);
        GLFL_LOAD_FUNCTION(Uniform1uiv);
        GLFL_LOAD_FUNCTION(Uniform2uiv);
        GLFL_LOAD_FUNCTION(Uniform3uiv);
        GLFL_LOAD_FUNCTION(Uniform4uiv);
        GLFL_LOAD_FUNCTION(ClearBufferiv);
        GLFL_LOAD_FUNCTION(ClearBufferuiv);
        GLFL_LOAD_FUNCTION(ClearBufferfv);
        GLFL_LOAD_FUNCTION(ClearBufferfi);
        GLFL_LOAD_FUNCTION(GetStringi);
        GLFL_LOAD_FUNCTION(CopyBufferSubData);
        GLFL_LOAD_FUNCTION(GetUniformIndices);
        GLFL_LOAD_FUNCTION(GetActiveUniformsiv);
        GLFL_LOAD_FUNCTION(GetUniformBlockIndex);
        GLFL_LOAD_FUNCTION(GetActiveUniformBlockiv);
        GLFL_LOAD_FUNCTION(GetActiveUniformBlockName);
        GLFL_LOAD_FUNCTION(UniformBlockBinding);
        GLFL_LOAD_FUNCTION(DrawArraysInstanced);
        GLFL_LOAD_FUNCTION(DrawElementsInstanced);
        GLFL_LOAD_FUNCTION(FenceSync);
        GLFL_LOAD_FUNCTION(IsSync);
        GLFL_LOAD_FUNCTION(DeleteSync);
        GLFL_LOAD_FUNCTION(ClientWaitSync);
        GLFL_LOAD_FUNCTION(WaitSync);
        GLFL_LOAD_FUNCTION(GetInteger64v);
        GLFL_LOAD_FUNCTION(GetSynciv);
        GLFL_LOAD_FUNCTION(GetInteger64i_v);
        GLFL_LOAD_FUNCTION(GetBufferParameteri64v);
        GLFL_LOAD_FUNCTION(GenSamplers);
        GLFL_LOAD_FUNCTION(DeleteSamplers);
        GLFL_LOAD_FUNCTION(IsSampler);
        GLFL_LOAD_FUNCTION(BindSampler);
        GLFL_LOAD_FUNCTION(SamplerParameteri);
        GLFL_LOAD_FUNCTION(SamplerParameteriv);
        GLFL_LOAD_FUNCTION(SamplerParameterf);
        GLFL_LOAD_FUNCTION(SamplerParameterfv);
        GLFL_LOAD_FUNCTION(GetSamplerParameteriv);
        GLFL_LOAD_FUNCTION(GetSamplerParameterfv);
        GLFL_LOAD_FUNCTION(VertexAttribDivisor);
        GLFL_LOAD_FUNCTION(BindTransformFeedback);
        GLFL_LOAD_FUNCTION(DeleteTransformFeedbacks);
        GLFL_LOAD_FUNCTION(GenTransformFeedbacks);
        GLFL_LOAD_FUNCTION(IsTransformFeedback);
        GLFL_LOAD_FUNCTION(PauseTransformFeedback);
        GLFL_LOAD_FUNCTION(ResumeTransformFeedback);
        GLFL_LOAD_FUNCTION(GetProgramBinary);
        GLFL_LOAD_FUNCTION(ProgramBinary);
        GLFL_LOAD_FUNCTION(ProgramParameteri);
        GLFL_LOAD_FUNCTION(InvalidateFramebuffer);
        GLFL_LOAD_FUNCTION(InvalidateSubFramebuffer);
        GLFL_LOAD_FUNCTION(TexStorage2D);
        GLFL_LOAD_FUNCTION(TexStorage3D);
        GLFL_LOAD_FUNCTION(GetInternalformativ);
      case 0x10000 * 2 + 0:
        GLFL_LOAD_FUNCTION(ActiveTexture);
        GLFL_LOAD_FUNCTION(AttachShader);
        GLFL_LOAD_FUNCTION(BindAttribLocation);
        GLFL_LOAD_FUNCTION(BindBuffer);
        GLFL_LOAD_FUNCTION(BindFramebuffer);
        GLFL_LOAD_FUNCTION(BindRenderbuffer);
        GLFL_LOAD_FUNCTION(BindTexture);
        GLFL_LOAD_FUNCTION(BlendColor);
        GLFL_LOAD_FUNCTION(BlendEquation);
        GLFL_LOAD_FUNCTION(BlendEquationSeparate);
        GLFL_LOAD_FUNCTION(BlendFunc);
        GLFL_LOAD_FUNCTION(BlendFuncSeparate);
        GLFL_LOAD_FUNCTION(BufferData);
        GLFL_LOAD_FUNCTION(BufferSubData);
        GLFL_LOAD_FUNCTION(CheckFramebufferStatus);
        GLFL_LOAD_FUNCTION(Clear);
        GLFL_LOAD_FUNCTION(ClearColor);
        GLFL_LOAD_FUNCTION(ClearDepthf);
        GLFL_LOAD_FUNCTION(ClearStencil);
        GLFL_LOAD_FUNCTION(ColorMask);
        GLFL_LOAD_FUNCTION(CompileShader);
        GLFL_LOAD_FUNCTION(CompressedTexImage2D);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage2D);
        GLFL_LOAD_FUNCTION(CopyTexImage2D);
        GLFL_LOAD_FUNCTION(CopyTexSubImage2D);
        GLFL_LOAD_FUNCTION(CreateProgram);
        GLFL_LOAD_FUNCTION(CreateShader);
        GLFL_LOAD_FUNCTION(CullFace);
        GLFL_LOAD_FUNCTION(DeleteBuffers);
        GLFL_LOAD_FUNCTION(DeleteFramebuffers);
        GLFL_LOAD_FUNCTION(DeleteProgram);
        GLFL_LOAD_FUNCTION(DeleteRenderbuffers);
        GLFL_LOAD_FUNCTION(DeleteShader);
        GLFL_LOAD_FUNCTION(DeleteTextures);
        GLFL_LOAD_FUNCTION(DepthFunc);
        GLFL_LOAD_FUNCTION(DepthMask);
        GLFL_LOAD_FUNCTION(DepthRangef);
        GLFL_LOAD_FUNCTION(DetachShader);
        GLFL_LOAD_FUNCTION(Disable);
        GLFL_LOAD_FUNCTION(DisableVertexAttribArray);
        GLFL_LOAD_FUNCTION(DrawArrays);
        GLFL_LOAD_FUNCTION(DrawElements);
        GLFL_LOAD_FUNCTION(Enable);
        GLFL_LOAD_FUNCTION(EnableVertexAttribArray);
        GLFL_LOAD_FUNCTION(Finish);
        GLFL_LOAD_FUNCTION(Flush);
        GLFL_LOAD_FUNCTION(FramebufferRenderbuffer);
        GLFL_LOAD_FUNCTION(FramebufferTexture2D);
        GLFL_LOAD_FUNCTION(FrontFace);
        GLFL_LOAD_FUNCTION(GenBuffers);
        GLFL_LOAD_FUNCTION(GenerateMipmap);
        GLFL_LOAD_FUNCTION(GenFramebuffers);
        GLFL_LOAD_FUNCTION(GenRenderbuffers);
        GLFL_LOAD_FUNCTION(GenTextures);
        GLFL_LOAD_FUNCTION(GetActiveAttrib);
        GLFL_LOAD_FUNCTION(GetActiveUniform);
        GLFL_LOAD_FUNCTION(GetAttachedShaders);
        GLFL_LOAD_FUNCTION(GetAttribLocation);
        GLFL_LOAD_FUNCTION(GetBooleanv);
        GLFL_LOAD_FUNCTION(GetBufferParameteriv);
        GLFL_LOAD_FUNCTION(GetError);
        GLFL_LOAD_FUNCTION(GetFloatv);
        GLFL_LOAD_FUNCTION(GetFramebufferAttachmentParameteriv);
        GLFL_LOAD_FUNCTION(GetIntegerv);
        GLFL_LOAD_FUNCTION(GetProgramiv);
        GLFL_LOAD_FUNCTION(GetProgramInfoLog);
        GLFL_LOAD_FUNCTION(GetRenderbufferParameteriv);
        GLFL_LOAD_FUNCTION(GetShaderiv);
        GLFL_LOAD_FUNCTION(GetShaderInfoLog);
        GLFL_LOAD_FUNCTION(GetShaderPrecisionFormat);
        GLFL_LOAD_FUNCTION(GetShaderSource);
        GLFL_LOAD_FUNCTION(GetString);
        GLFL_LOAD_FUNCTION(GetTexParameterfv);
        GLFL_LOAD_FUNCTION(GetTexParameteriv);
        GLFL_LOAD_FUNCTION(GetUniformfv);
        GLFL_LOAD_FUNCTION(GetUniformiv);
        GLFL_LOAD_FUNCTION(GetUniformLocation);
        GLFL_LOAD_FUNCTION(GetVertexAttribfv);
        GLFL_LOAD_FUNCTION(GetVertexAttribiv);
        GLFL_LOAD_FUNCTION(GetVertexAttribPointerv);
        GLFL_LOAD_FUNCTION(Hint);
        GLFL_LOAD_FUNCTION(IsBuffer);
        GLFL_LOAD_FUNCTION(IsEnabled);
        GLFL_LOAD_FUNCTION(IsFramebuffer);
        GLFL_LOAD_FUNCTION(IsProgram);
        GLFL_LOAD_FUNCTION(IsRenderbuffer);
        GLFL_LOAD_FUNCTION(IsShader);
        GLFL_LOAD_FUNCTION(IsTexture);
        GLFL_LOAD_FUNCTION(LineWidth);
        GLFL_LOAD_FUNCTION(LinkProgram);
        GLFL_LOAD_FUNCTION(PixelStorei);
        GLFL_LOAD_FUNCTION(PolygonOffset);
        GLFL_LOAD_FUNCTION(ReadPixels);
        GLFL_LOAD_FUNCTION(ReleaseShaderCompiler);
        GLFL_LOAD_FUNCTION(RenderbufferStorage);
        GLFL_LOAD_FUNCTION(SampleCoverage);
        GLFL_LOAD_FUNCTION(Scissor);
        GLFL_LOAD_FUNCTION(ShaderBinary);
        GLFL_LOAD_FUNCTION(ShaderSource);
        GLFL_LOAD_FUNCTION(StencilFunc);
        GLFL_LOAD_FUNCTION(StencilFuncSeparate);
        GLFL_LOAD_FUNCTION(StencilMask);
        GLFL_LOAD_FUNCTION(StencilMaskSeparate);
        GLFL_LOAD_FUNCTION(StencilOp);
        GLFL_LOAD_FUNCTION(StencilOpSeparate);
        GLFL_LOAD_FUNCTION(TexImage2D);
        GLFL_LOAD_FUNCTION(TexParameterf);
        GLFL_LOAD_FUNCTION(TexParameterfv);
        GLFL_LOAD_FUNCTION(TexParameteri);
        GLFL_LOAD_FUNCTION(TexParameteriv);
        GLFL_LOAD_FUNCTION(TexSubImage2D);
        GLFL_LOAD_FUNCTION(Uniform1f);
        GLFL_LOAD_FUNCTION(Uniform1fv);
        GLFL_LOAD_FUNCTION(Uniform1i);
        GLFL_LOAD_FUNCTION(Uniform1iv);
        GLFL_LOAD_FUNCTION(Uniform2f);
        GLFL_LOAD_FUNCTION(Uniform2fv);
        GLFL_LOAD_FUNCTION(Uniform2i);
        GLFL_LOAD_FUNCTION(Uniform2iv);
        GLFL_LOAD_FUNCTION(Uniform3f);
        GLFL_LOAD_FUNCTION(Uniform3fv);
        GLFL_LOAD_FUNCTION(Uniform3i);
        GLFL_LOAD_FUNCTION(Uniform3iv);
        GLFL_LOAD_FUNCTION(Uniform4f);
        GLFL_LOAD_FUNCTION(Uniform4fv);
        GLFL_LOAD_FUNCTION(Uniform4i);
        GLFL_LOAD_FUNCTION(Uniform4iv);
        GLFL_LOAD_FUNCTION(UniformMatrix2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4fv);
        GLFL_LOAD_FUNCTION(UseProgram);
        GLFL_LOAD_FUNCTION(ValidateProgram);
        GLFL_LOAD_FUNCTION(VertexAttrib1f);
        GLFL_LOAD_FUNCTION(VertexAttrib1fv);
        GLFL_LOAD_FUNCTION(VertexAttrib2f);
        GLFL_LOAD_FUNCTION(VertexAttrib2fv);
        GLFL_LOAD_FUNCTION(VertexAttrib3f);
        GLFL_LOAD_FUNCTION(VertexAttrib3fv);
        GLFL_LOAD_FUNCTION(VertexAttrib4f);
        GLFL_LOAD_FUNCTION(VertexAttrib4fv);
        GLFL_LOAD_FUNCTION(VertexAttribPointer);
        GLFL_LOAD_FUNCTION(Viewport);
    }
}
static void load_version_glsc2(int major, int minor)
{
    switch (0x10000 * major + minor)
    {
      default:
      case 0x10000 * 2 + 0:
        GLFL_LOAD_FUNCTION(ActiveTexture);
        GLFL_LOAD_FUNCTION(BindBuffer);
        GLFL_LOAD_FUNCTION(BindFramebuffer);
        GLFL_LOAD_FUNCTION(BindRenderbuffer);
        GLFL_LOAD_FUNCTION(BindTexture);
        GLFL_LOAD_FUNCTION(BlendColor);
        GLFL_LOAD_FUNCTION(BlendEquation);
        GLFL_LOAD_FUNCTION(BlendEquationSeparate);
        GLFL_LOAD_FUNCTION(BlendFunc);
        GLFL_LOAD_FUNCTION(BlendFuncSeparate);
        GLFL_LOAD_FUNCTION(BufferData);
        GLFL_LOAD_FUNCTION(BufferSubData);
        GLFL_LOAD_FUNCTION(CheckFramebufferStatus);
        GLFL_LOAD_FUNCTION(Clear);
        GLFL_LOAD_FUNCTION(ClearColor);
        GLFL_LOAD_FUNCTION(ClearDepthf);
        GLFL_LOAD_FUNCTION(ClearStencil);
        GLFL_LOAD_FUNCTION(ColorMask);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage2D);
        GLFL_LOAD_FUNCTION(CreateProgram);
        GLFL_LOAD_FUNCTION(CullFace);
        GLFL_LOAD_FUNCTION(DepthFunc);
        GLFL_LOAD_FUNCTION(DepthMask);
        GLFL_LOAD_FUNCTION(DepthRangef);
        GLFL_LOAD_FUNCTION(Disable);
        GLFL_LOAD_FUNCTION(DisableVertexAttribArray);
        GLFL_LOAD_FUNCTION(DrawArrays);
        GLFL_LOAD_FUNCTION(DrawRangeElements);
        GLFL_LOAD_FUNCTION(Enable);
        GLFL_LOAD_FUNCTION(EnableVertexAttribArray);
        GLFL_LOAD_FUNCTION(Finish);
        GLFL_LOAD_FUNCTION(Flush);
        GLFL_LOAD_FUNCTION(FramebufferRenderbuffer);
        GLFL_LOAD_FUNCTION(FramebufferTexture2D);
        GLFL_LOAD_FUNCTION(FrontFace);
        GLFL_LOAD_FUNCTION(GenBuffers);
        GLFL_LOAD_FUNCTION(GenerateMipmap);
        GLFL_LOAD_FUNCTION(GenFramebuffers);
        GLFL_LOAD_FUNCTION(GenRenderbuffers);
        GLFL_LOAD_FUNCTION(GenTextures);
        GLFL_LOAD_FUNCTION(GetAttribLocation);
        GLFL_LOAD_FUNCTION(GetBooleanv);
        GLFL_LOAD_FUNCTION(GetBufferParameteriv);
        GLFL_LOAD_FUNCTION(GetError);
        GLFL_LOAD_FUNCTION(GetFloatv);
        GLFL_LOAD_FUNCTION(GetFramebufferAttachmentParameteriv);
        GLFL_LOAD_FUNCTION(GetGraphicsResetStatus);
        GLFL_LOAD_FUNCTION(GetIntegerv);
        GLFL_LOAD_FUNCTION(GetProgramiv);
        GLFL_LOAD_FUNCTION(GetRenderbufferParameteriv);
        GLFL_LOAD_FUNCTION(GetString);
        GLFL_LOAD_FUNCTION(GetTexParameterfv);
        GLFL_LOAD_FUNCTION(GetTexParameteriv);
        GLFL_LOAD_FUNCTION(GetnUniformfv);
        GLFL_LOAD_FUNCTION(GetnUniformiv);
        GLFL_LOAD_FUNCTION(GetUniformLocation);
        GLFL_LOAD_FUNCTION(GetVertexAttribfv);
        GLFL_LOAD_FUNCTION(GetVertexAttribiv);
        GLFL_LOAD_FUNCTION(GetVertexAttribPointerv);
        GLFL_LOAD_FUNCTION(Hint);
        GLFL_LOAD_FUNCTION(IsEnabled);
        GLFL_LOAD_FUNCTION(LineWidth);
        GLFL_LOAD_FUNCTION(PixelStorei);
        GLFL_LOAD_FUNCTION(PolygonOffset);
        GLFL_LOAD_FUNCTION(ProgramBinary);
        GLFL_LOAD_FUNCTION(ReadnPixels);
        GLFL_LOAD_FUNCTION(RenderbufferStorage);
        GLFL_LOAD_FUNCTION(SampleCoverage);
        GLFL_LOAD_FUNCTION(Scissor);
        GLFL_LOAD_FUNCTION(StencilFunc);
        GLFL_LOAD_FUNCTION(StencilFuncSeparate);
        GLFL_LOAD_FUNCTION(StencilMask);
        GLFL_LOAD_FUNCTION(StencilMaskSeparate);
        GLFL_LOAD_FUNCTION(StencilOp);
        GLFL_LOAD_FUNCTION(StencilOpSeparate);
        GLFL_LOAD_FUNCTION(TexStorage2D);
        GLFL_LOAD_FUNCTION(TexParameterf);
        GLFL_LOAD_FUNCTION(TexParameterfv);
        GLFL_LOAD_FUNCTION(TexParameteri);
        GLFL_LOAD_FUNCTION(TexParameteriv);
        GLFL_LOAD_FUNCTION(TexSubImage2D);
        GLFL_LOAD_FUNCTION(Uniform1f);
        GLFL_LOAD_FUNCTION(Uniform1fv);
        GLFL_LOAD_FUNCTION(Uniform1i);
        GLFL_LOAD_FUNCTION(Uniform1iv);
        GLFL_LOAD_FUNCTION(Uniform2f);
        GLFL_LOAD_FUNCTION(Uniform2fv);
        GLFL_LOAD_FUNCTION(Uniform2i);
        GLFL_LOAD_FUNCTION(Uniform2iv);
        GLFL_LOAD_FUNCTION(Uniform3f);
        GLFL_LOAD_FUNCTION(Uniform3fv);
        GLFL_LOAD_FUNCTION(Uniform3i);
        GLFL_LOAD_FUNCTION(Uniform3iv);
        GLFL_LOAD_FUNCTION(Uniform4f);
        GLFL_LOAD_FUNCTION(Uniform4fv);
        GLFL_LOAD_FUNCTION(Uniform4i);
        GLFL_LOAD_FUNCTION(Uniform4iv);
        GLFL_LOAD_FUNCTION(UniformMatrix2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4fv);
        GLFL_LOAD_FUNCTION(UseProgram);
        GLFL_LOAD_FUNCTION(VertexAttrib1f);
        GLFL_LOAD_FUNCTION(VertexAttrib1fv);
        GLFL_LOAD_FUNCTION(VertexAttrib2f);
        GLFL_LOAD_FUNCTION(VertexAttrib2fv);
        GLFL_LOAD_FUNCTION(VertexAttrib3f);
        GLFL_LOAD_FUNCTION(VertexAttrib3fv);
        GLFL_LOAD_FUNCTION(VertexAttrib4f);
        GLFL_LOAD_FUNCTION(VertexAttrib4fv);
        GLFL_LOAD_FUNCTION(VertexAttribPointer);
        GLFL_LOAD_FUNCTION(Viewport);
    }
}

void glfl::load_gl(int major, int minor)
{
    load_version_gl(major, minor);
}
void glfl::load_gles(int major, int minor)
{
    if (major == 1 && minor == 0)
    {
        load_version_gles1(major, minor);
        return;
    }
    load_version_gles2(major, minor);
}
void glfl::load_glsc(int major, int minor)
{
    load_version_glsc2(major, minor);
}

void glfl::load_extension_GL_3DFX_multisample() {}
void glfl::load_extension_GL_3DFX_tbuffer()
{
    GLFL_LOAD_FUNCTION(TbufferMask3DFX);
}
void glfl::load_extension_GL_3DFX_texture_compression_FXT1() {}
void glfl::load_extension_GL_AMD_blend_minmax_factor() {}
void glfl::load_extension_GL_AMD_compressed_3DC_texture() {}
void glfl::load_extension_GL_AMD_compressed_ATC_texture() {}
void glfl::load_extension_GL_AMD_conservative_depth() {}
void glfl::load_extension_GL_AMD_debug_output()
{
    GLFL_LOAD_FUNCTION(DebugMessageEnableAMD);
    GLFL_LOAD_FUNCTION(DebugMessageInsertAMD);
    GLFL_LOAD_FUNCTION(DebugMessageCallbackAMD);
    GLFL_LOAD_FUNCTION(GetDebugMessageLogAMD);
}
void glfl::load_extension_GL_AMD_depth_clamp_separate() {}
void glfl::load_extension_GL_AMD_draw_buffers_blend()
{
    GLFL_LOAD_FUNCTION(BlendFuncIndexedAMD);
    GLFL_LOAD_FUNCTION(BlendFuncSeparateIndexedAMD);
    GLFL_LOAD_FUNCTION(BlendEquationIndexedAMD);
    GLFL_LOAD_FUNCTION(BlendEquationSeparateIndexedAMD);
}
void glfl::load_extension_GL_AMD_framebuffer_sample_positions()
{
    GLFL_LOAD_FUNCTION(FramebufferSamplePositionsfvAMD);
    GLFL_LOAD_FUNCTION(NamedFramebufferSamplePositionsfvAMD);
    GLFL_LOAD_FUNCTION(GetFramebufferParameterfvAMD);
    GLFL_LOAD_FUNCTION(GetNamedFramebufferParameterfvAMD);
}
void glfl::load_extension_GL_AMD_gcn_shader() {}
void glfl::load_extension_GL_AMD_gpu_shader_half_float() {}
void glfl::load_extension_GL_AMD_gpu_shader_int64()
{
    GLFL_LOAD_FUNCTION(Uniform1i64NV);
    GLFL_LOAD_FUNCTION(Uniform2i64NV);
    GLFL_LOAD_FUNCTION(Uniform3i64NV);
    GLFL_LOAD_FUNCTION(Uniform4i64NV);
    GLFL_LOAD_FUNCTION(Uniform1i64vNV);
    GLFL_LOAD_FUNCTION(Uniform2i64vNV);
    GLFL_LOAD_FUNCTION(Uniform3i64vNV);
    GLFL_LOAD_FUNCTION(Uniform4i64vNV);
    GLFL_LOAD_FUNCTION(Uniform1ui64NV);
    GLFL_LOAD_FUNCTION(Uniform2ui64NV);
    GLFL_LOAD_FUNCTION(Uniform3ui64NV);
    GLFL_LOAD_FUNCTION(Uniform4ui64NV);
    GLFL_LOAD_FUNCTION(Uniform1ui64vNV);
    GLFL_LOAD_FUNCTION(Uniform2ui64vNV);
    GLFL_LOAD_FUNCTION(Uniform3ui64vNV);
    GLFL_LOAD_FUNCTION(Uniform4ui64vNV);
    GLFL_LOAD_FUNCTION(GetUniformi64vNV);
    GLFL_LOAD_FUNCTION(GetUniformui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform1i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform2i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform3i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform4i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform1i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform2i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform3i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform4i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui64vNV);
}
void glfl::load_extension_GL_AMD_interleaved_elements()
{
    GLFL_LOAD_FUNCTION(VertexAttribParameteriAMD);
}
void glfl::load_extension_GL_AMD_multi_draw_indirect()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysIndirectAMD);
    GLFL_LOAD_FUNCTION(MultiDrawElementsIndirectAMD);
}
void glfl::load_extension_GL_AMD_name_gen_delete()
{
    GLFL_LOAD_FUNCTION(GenNamesAMD);
    GLFL_LOAD_FUNCTION(DeleteNamesAMD);
    GLFL_LOAD_FUNCTION(IsNameAMD);
}
void glfl::load_extension_GL_AMD_occlusion_query_event()
{
    GLFL_LOAD_FUNCTION(QueryObjectParameteruiAMD);
}
void glfl::load_extension_GL_AMD_performance_monitor()
{
    GLFL_LOAD_FUNCTION(GetPerfMonitorGroupsAMD);
    GLFL_LOAD_FUNCTION(GetPerfMonitorCountersAMD);
    GLFL_LOAD_FUNCTION(GetPerfMonitorGroupStringAMD);
    GLFL_LOAD_FUNCTION(GetPerfMonitorCounterStringAMD);
    GLFL_LOAD_FUNCTION(GetPerfMonitorCounterInfoAMD);
    GLFL_LOAD_FUNCTION(GenPerfMonitorsAMD);
    GLFL_LOAD_FUNCTION(DeletePerfMonitorsAMD);
    GLFL_LOAD_FUNCTION(SelectPerfMonitorCountersAMD);
    GLFL_LOAD_FUNCTION(BeginPerfMonitorAMD);
    GLFL_LOAD_FUNCTION(EndPerfMonitorAMD);
    GLFL_LOAD_FUNCTION(GetPerfMonitorCounterDataAMD);
}
void glfl::load_extension_GL_AMD_pinned_memory() {}
void glfl::load_extension_GL_AMD_program_binary_Z400() {}
void glfl::load_extension_GL_AMD_query_buffer_object() {}
void glfl::load_extension_GL_AMD_sample_positions()
{
    GLFL_LOAD_FUNCTION(SetMultisamplefvAMD);
}
void glfl::load_extension_GL_AMD_seamless_cubemap_per_texture() {}
void glfl::load_extension_GL_AMD_shader_atomic_counter_ops() {}
void glfl::load_extension_GL_AMD_shader_ballot() {}
void glfl::load_extension_GL_AMD_shader_stencil_export() {}
void glfl::load_extension_GL_AMD_shader_trinary_minmax() {}
void glfl::load_extension_GL_AMD_shader_explicit_vertex_parameter() {}
void glfl::load_extension_GL_AMD_sparse_texture()
{
    GLFL_LOAD_FUNCTION(TexStorageSparseAMD);
    GLFL_LOAD_FUNCTION(TextureStorageSparseAMD);
}
void glfl::load_extension_GL_AMD_stencil_operation_extended()
{
    GLFL_LOAD_FUNCTION(StencilOpValueAMD);
}
void glfl::load_extension_GL_AMD_texture_texture4() {}
void glfl::load_extension_GL_AMD_transform_feedback3_lines_triangles() {}
void glfl::load_extension_GL_AMD_transform_feedback4() {}
void glfl::load_extension_GL_AMD_vertex_shader_layer() {}
void glfl::load_extension_GL_AMD_vertex_shader_tessellator()
{
    GLFL_LOAD_FUNCTION(TessellationFactorAMD);
    GLFL_LOAD_FUNCTION(TessellationModeAMD);
}
void glfl::load_extension_GL_AMD_vertex_shader_viewport_index() {}
void glfl::load_extension_GL_ANDROID_extension_pack_es31a() {}
void glfl::load_extension_GL_ANGLE_depth_texture() {}
void glfl::load_extension_GL_ANGLE_framebuffer_blit()
{
    GLFL_LOAD_FUNCTION(BlitFramebufferANGLE);
}
void glfl::load_extension_GL_ANGLE_framebuffer_multisample()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleANGLE);
}
void glfl::load_extension_GL_ANGLE_instanced_arrays()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedANGLE);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedANGLE);
    GLFL_LOAD_FUNCTION(VertexAttribDivisorANGLE);
}
void glfl::load_extension_GL_ANGLE_pack_reverse_row_order() {}
void glfl::load_extension_GL_ANGLE_program_binary() {}
void glfl::load_extension_GL_ANGLE_texture_compression_dxt3() {}
void glfl::load_extension_GL_ANGLE_texture_compression_dxt5() {}
void glfl::load_extension_GL_ANGLE_texture_usage() {}
void glfl::load_extension_GL_ANGLE_translated_shader_source()
{
    GLFL_LOAD_FUNCTION(GetTranslatedShaderSourceANGLE);
}
void glfl::load_extension_GL_APPLE_aux_depth_stencil() {}
void glfl::load_extension_GL_APPLE_client_storage() {}
void glfl::load_extension_GL_APPLE_clip_distance() {}
void glfl::load_extension_GL_APPLE_color_buffer_packed_float() {}
void glfl::load_extension_GL_APPLE_copy_texture_levels()
{
    GLFL_LOAD_FUNCTION(CopyTextureLevelsAPPLE);
}
void glfl::load_extension_GL_APPLE_element_array()
{
    GLFL_LOAD_FUNCTION(ElementPointerAPPLE);
    GLFL_LOAD_FUNCTION(DrawElementArrayAPPLE);
    GLFL_LOAD_FUNCTION(DrawRangeElementArrayAPPLE);
    GLFL_LOAD_FUNCTION(MultiDrawElementArrayAPPLE);
    GLFL_LOAD_FUNCTION(MultiDrawRangeElementArrayAPPLE);
}
void glfl::load_extension_GL_APPLE_fence()
{
    GLFL_LOAD_FUNCTION(GenFencesAPPLE);
    GLFL_LOAD_FUNCTION(DeleteFencesAPPLE);
    GLFL_LOAD_FUNCTION(SetFenceAPPLE);
    GLFL_LOAD_FUNCTION(IsFenceAPPLE);
    GLFL_LOAD_FUNCTION(TestFenceAPPLE);
    GLFL_LOAD_FUNCTION(FinishFenceAPPLE);
    GLFL_LOAD_FUNCTION(TestObjectAPPLE);
    GLFL_LOAD_FUNCTION(FinishObjectAPPLE);
}
void glfl::load_extension_GL_APPLE_float_pixels() {}
void glfl::load_extension_GL_APPLE_flush_buffer_range()
{
    GLFL_LOAD_FUNCTION(BufferParameteriAPPLE);
    GLFL_LOAD_FUNCTION(FlushMappedBufferRangeAPPLE);
}
void glfl::load_extension_GL_APPLE_framebuffer_multisample()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleAPPLE);
    GLFL_LOAD_FUNCTION(ResolveMultisampleFramebufferAPPLE);
}
void glfl::load_extension_GL_APPLE_object_purgeable()
{
    GLFL_LOAD_FUNCTION(ObjectPurgeableAPPLE);
    GLFL_LOAD_FUNCTION(ObjectUnpurgeableAPPLE);
    GLFL_LOAD_FUNCTION(GetObjectParameterivAPPLE);
}
void glfl::load_extension_GL_APPLE_rgb_422() {}
void glfl::load_extension_GL_APPLE_row_bytes() {}
void glfl::load_extension_GL_APPLE_specular_vector() {}
void glfl::load_extension_GL_APPLE_sync()
{
    GLFL_LOAD_FUNCTION(FenceSyncAPPLE);
    GLFL_LOAD_FUNCTION(IsSyncAPPLE);
    GLFL_LOAD_FUNCTION(DeleteSyncAPPLE);
    GLFL_LOAD_FUNCTION(ClientWaitSyncAPPLE);
    GLFL_LOAD_FUNCTION(WaitSyncAPPLE);
    GLFL_LOAD_FUNCTION(GetInteger64vAPPLE);
    GLFL_LOAD_FUNCTION(GetSyncivAPPLE);
}
void glfl::load_extension_GL_APPLE_texture_2D_limited_npot() {}
void glfl::load_extension_GL_APPLE_texture_format_BGRA8888() {}
void glfl::load_extension_GL_APPLE_texture_max_level() {}
void glfl::load_extension_GL_APPLE_texture_packed_float() {}
void glfl::load_extension_GL_APPLE_texture_range()
{
    GLFL_LOAD_FUNCTION(TextureRangeAPPLE);
    GLFL_LOAD_FUNCTION(GetTexParameterPointervAPPLE);
}
void glfl::load_extension_GL_APPLE_transform_hint() {}
void glfl::load_extension_GL_APPLE_vertex_array_object()
{
    GLFL_LOAD_FUNCTION(BindVertexArrayAPPLE);
    GLFL_LOAD_FUNCTION(DeleteVertexArraysAPPLE);
    GLFL_LOAD_FUNCTION(GenVertexArraysAPPLE);
    GLFL_LOAD_FUNCTION(IsVertexArrayAPPLE);
}
void glfl::load_extension_GL_APPLE_vertex_array_range()
{
    GLFL_LOAD_FUNCTION(VertexArrayRangeAPPLE);
    GLFL_LOAD_FUNCTION(FlushVertexArrayRangeAPPLE);
    GLFL_LOAD_FUNCTION(VertexArrayParameteriAPPLE);
}
void glfl::load_extension_GL_APPLE_vertex_program_evaluators()
{
    GLFL_LOAD_FUNCTION(EnableVertexAttribAPPLE);
    GLFL_LOAD_FUNCTION(DisableVertexAttribAPPLE);
    GLFL_LOAD_FUNCTION(IsVertexAttribEnabledAPPLE);
    GLFL_LOAD_FUNCTION(MapVertexAttrib1dAPPLE);
    GLFL_LOAD_FUNCTION(MapVertexAttrib1fAPPLE);
    GLFL_LOAD_FUNCTION(MapVertexAttrib2dAPPLE);
    GLFL_LOAD_FUNCTION(MapVertexAttrib2fAPPLE);
}
void glfl::load_extension_GL_APPLE_ycbcr_422() {}
void glfl::load_extension_GL_ARB_ES2_compatibility()
{
    GLFL_LOAD_FUNCTION(ReleaseShaderCompiler);
    GLFL_LOAD_FUNCTION(ShaderBinary);
    GLFL_LOAD_FUNCTION(GetShaderPrecisionFormat);
    GLFL_LOAD_FUNCTION(DepthRangef);
    GLFL_LOAD_FUNCTION(ClearDepthf);
}
void glfl::load_extension_GL_ARB_ES3_1_compatibility()
{
    GLFL_LOAD_FUNCTION(MemoryBarrierByRegion);
}
void glfl::load_extension_GL_ARB_ES3_2_compatibility()
{
    GLFL_LOAD_FUNCTION(PrimitiveBoundingBoxARB);
}
void glfl::load_extension_GL_ARB_ES3_compatibility() {}
void glfl::load_extension_GL_ARB_arrays_of_arrays() {}
void glfl::load_extension_GL_ARB_base_instance()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedBaseInstance);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseInstance);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertexBaseInstance);
}
void glfl::load_extension_GL_ARB_bindless_texture()
{
    GLFL_LOAD_FUNCTION(GetTextureHandleARB);
    GLFL_LOAD_FUNCTION(GetTextureSamplerHandleARB);
    GLFL_LOAD_FUNCTION(MakeTextureHandleResidentARB);
    GLFL_LOAD_FUNCTION(MakeTextureHandleNonResidentARB);
    GLFL_LOAD_FUNCTION(GetImageHandleARB);
    GLFL_LOAD_FUNCTION(MakeImageHandleResidentARB);
    GLFL_LOAD_FUNCTION(MakeImageHandleNonResidentARB);
    GLFL_LOAD_FUNCTION(UniformHandleui64ARB);
    GLFL_LOAD_FUNCTION(UniformHandleui64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniformHandleui64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniformHandleui64vARB);
    GLFL_LOAD_FUNCTION(IsTextureHandleResidentARB);
    GLFL_LOAD_FUNCTION(IsImageHandleResidentARB);
    GLFL_LOAD_FUNCTION(VertexAttribL1ui64ARB);
    GLFL_LOAD_FUNCTION(VertexAttribL1ui64vARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribLui64vARB);
}
void glfl::load_extension_GL_ARB_blend_func_extended()
{
    GLFL_LOAD_FUNCTION(BindFragDataLocationIndexed);
    GLFL_LOAD_FUNCTION(GetFragDataIndex);
}
void glfl::load_extension_GL_ARB_buffer_storage()
{
    GLFL_LOAD_FUNCTION(BufferStorage);
}
void glfl::load_extension_GL_ARB_cl_event()
{
    GLFL_LOAD_FUNCTION(CreateSyncFromCLeventARB);
}
void glfl::load_extension_GL_ARB_clear_buffer_object()
{
    GLFL_LOAD_FUNCTION(ClearBufferData);
    GLFL_LOAD_FUNCTION(ClearBufferSubData);
}
void glfl::load_extension_GL_ARB_clear_texture()
{
    GLFL_LOAD_FUNCTION(ClearTexImage);
    GLFL_LOAD_FUNCTION(ClearTexSubImage);
}
void glfl::load_extension_GL_ARB_clip_control()
{
    GLFL_LOAD_FUNCTION(ClipControl);
}
void glfl::load_extension_GL_ARB_color_buffer_float()
{
    GLFL_LOAD_FUNCTION(ClampColorARB);
}
void glfl::load_extension_GL_ARB_compatibility() {}
void glfl::load_extension_GL_ARB_compressed_texture_pixel_storage() {}
void glfl::load_extension_GL_ARB_compute_shader()
{
    GLFL_LOAD_FUNCTION(DispatchCompute);
    GLFL_LOAD_FUNCTION(DispatchComputeIndirect);
}
void glfl::load_extension_GL_ARB_compute_variable_group_size()
{
    GLFL_LOAD_FUNCTION(DispatchComputeGroupSizeARB);
}
void glfl::load_extension_GL_ARB_conditional_render_inverted() {}
void glfl::load_extension_GL_ARB_conservative_depth() {}
void glfl::load_extension_GL_ARB_copy_buffer()
{
    GLFL_LOAD_FUNCTION(CopyBufferSubData);
}
void glfl::load_extension_GL_ARB_copy_image()
{
    GLFL_LOAD_FUNCTION(CopyImageSubData);
}
void glfl::load_extension_GL_ARB_cull_distance() {}
void glfl::load_extension_GL_ARB_debug_output()
{
    GLFL_LOAD_FUNCTION(DebugMessageControlARB);
    GLFL_LOAD_FUNCTION(DebugMessageInsertARB);
    GLFL_LOAD_FUNCTION(DebugMessageCallbackARB);
    GLFL_LOAD_FUNCTION(GetDebugMessageLogARB);
}
void glfl::load_extension_GL_ARB_depth_buffer_float() {}
void glfl::load_extension_GL_ARB_depth_clamp() {}
void glfl::load_extension_GL_ARB_depth_texture() {}
void glfl::load_extension_GL_ARB_derivative_control() {}
void glfl::load_extension_GL_ARB_direct_state_access()
{
    GLFL_LOAD_FUNCTION(CreateTransformFeedbacks);
    GLFL_LOAD_FUNCTION(TransformFeedbackBufferBase);
    GLFL_LOAD_FUNCTION(TransformFeedbackBufferRange);
    GLFL_LOAD_FUNCTION(GetTransformFeedbackiv);
    GLFL_LOAD_FUNCTION(GetTransformFeedbacki_v);
    GLFL_LOAD_FUNCTION(GetTransformFeedbacki64_v);
    GLFL_LOAD_FUNCTION(CreateBuffers);
    GLFL_LOAD_FUNCTION(NamedBufferStorage);
    GLFL_LOAD_FUNCTION(NamedBufferData);
    GLFL_LOAD_FUNCTION(NamedBufferSubData);
    GLFL_LOAD_FUNCTION(CopyNamedBufferSubData);
    GLFL_LOAD_FUNCTION(ClearNamedBufferData);
    GLFL_LOAD_FUNCTION(ClearNamedBufferSubData);
    GLFL_LOAD_FUNCTION(MapNamedBuffer);
    GLFL_LOAD_FUNCTION(MapNamedBufferRange);
    GLFL_LOAD_FUNCTION(UnmapNamedBuffer);
    GLFL_LOAD_FUNCTION(FlushMappedNamedBufferRange);
    GLFL_LOAD_FUNCTION(GetNamedBufferParameteriv);
    GLFL_LOAD_FUNCTION(GetNamedBufferParameteri64v);
    GLFL_LOAD_FUNCTION(GetNamedBufferPointerv);
    GLFL_LOAD_FUNCTION(GetNamedBufferSubData);
    GLFL_LOAD_FUNCTION(CreateFramebuffers);
    GLFL_LOAD_FUNCTION(NamedFramebufferRenderbuffer);
    GLFL_LOAD_FUNCTION(NamedFramebufferParameteri);
    GLFL_LOAD_FUNCTION(NamedFramebufferTexture);
    GLFL_LOAD_FUNCTION(NamedFramebufferTextureLayer);
    GLFL_LOAD_FUNCTION(NamedFramebufferDrawBuffer);
    GLFL_LOAD_FUNCTION(NamedFramebufferDrawBuffers);
    GLFL_LOAD_FUNCTION(NamedFramebufferReadBuffer);
    GLFL_LOAD_FUNCTION(InvalidateNamedFramebufferData);
    GLFL_LOAD_FUNCTION(InvalidateNamedFramebufferSubData);
    GLFL_LOAD_FUNCTION(ClearNamedFramebufferiv);
    GLFL_LOAD_FUNCTION(ClearNamedFramebufferuiv);
    GLFL_LOAD_FUNCTION(ClearNamedFramebufferfv);
    GLFL_LOAD_FUNCTION(ClearNamedFramebufferfi);
    GLFL_LOAD_FUNCTION(BlitNamedFramebuffer);
    GLFL_LOAD_FUNCTION(CheckNamedFramebufferStatus);
    GLFL_LOAD_FUNCTION(GetNamedFramebufferParameteriv);
    GLFL_LOAD_FUNCTION(GetNamedFramebufferAttachmentParameteriv);
    GLFL_LOAD_FUNCTION(CreateRenderbuffers);
    GLFL_LOAD_FUNCTION(NamedRenderbufferStorage);
    GLFL_LOAD_FUNCTION(NamedRenderbufferStorageMultisample);
    GLFL_LOAD_FUNCTION(GetNamedRenderbufferParameteriv);
    GLFL_LOAD_FUNCTION(CreateTextures);
    GLFL_LOAD_FUNCTION(TextureBuffer);
    GLFL_LOAD_FUNCTION(TextureBufferRange);
    GLFL_LOAD_FUNCTION(TextureStorage1D);
    GLFL_LOAD_FUNCTION(TextureStorage2D);
    GLFL_LOAD_FUNCTION(TextureStorage3D);
    GLFL_LOAD_FUNCTION(TextureStorage2DMultisample);
    GLFL_LOAD_FUNCTION(TextureStorage3DMultisample);
    GLFL_LOAD_FUNCTION(TextureSubImage1D);
    GLFL_LOAD_FUNCTION(TextureSubImage2D);
    GLFL_LOAD_FUNCTION(TextureSubImage3D);
    GLFL_LOAD_FUNCTION(CompressedTextureSubImage1D);
    GLFL_LOAD_FUNCTION(CompressedTextureSubImage2D);
    GLFL_LOAD_FUNCTION(CompressedTextureSubImage3D);
    GLFL_LOAD_FUNCTION(CopyTextureSubImage1D);
    GLFL_LOAD_FUNCTION(CopyTextureSubImage2D);
    GLFL_LOAD_FUNCTION(CopyTextureSubImage3D);
    GLFL_LOAD_FUNCTION(TextureParameterf);
    GLFL_LOAD_FUNCTION(TextureParameterfv);
    GLFL_LOAD_FUNCTION(TextureParameteri);
    GLFL_LOAD_FUNCTION(TextureParameterIiv);
    GLFL_LOAD_FUNCTION(TextureParameterIuiv);
    GLFL_LOAD_FUNCTION(TextureParameteriv);
    GLFL_LOAD_FUNCTION(GenerateTextureMipmap);
    GLFL_LOAD_FUNCTION(BindTextureUnit);
    GLFL_LOAD_FUNCTION(GetTextureImage);
    GLFL_LOAD_FUNCTION(GetCompressedTextureImage);
    GLFL_LOAD_FUNCTION(GetTextureLevelParameterfv);
    GLFL_LOAD_FUNCTION(GetTextureLevelParameteriv);
    GLFL_LOAD_FUNCTION(GetTextureParameterfv);
    GLFL_LOAD_FUNCTION(GetTextureParameterIiv);
    GLFL_LOAD_FUNCTION(GetTextureParameterIuiv);
    GLFL_LOAD_FUNCTION(GetTextureParameteriv);
    GLFL_LOAD_FUNCTION(CreateVertexArrays);
    GLFL_LOAD_FUNCTION(DisableVertexArrayAttrib);
    GLFL_LOAD_FUNCTION(EnableVertexArrayAttrib);
    GLFL_LOAD_FUNCTION(VertexArrayElementBuffer);
    GLFL_LOAD_FUNCTION(VertexArrayVertexBuffer);
    GLFL_LOAD_FUNCTION(VertexArrayVertexBuffers);
    GLFL_LOAD_FUNCTION(VertexArrayAttribBinding);
    GLFL_LOAD_FUNCTION(VertexArrayAttribFormat);
    GLFL_LOAD_FUNCTION(VertexArrayAttribIFormat);
    GLFL_LOAD_FUNCTION(VertexArrayAttribLFormat);
    GLFL_LOAD_FUNCTION(VertexArrayBindingDivisor);
    GLFL_LOAD_FUNCTION(GetVertexArrayiv);
    GLFL_LOAD_FUNCTION(GetVertexArrayIndexediv);
    GLFL_LOAD_FUNCTION(GetVertexArrayIndexed64iv);
    GLFL_LOAD_FUNCTION(CreateSamplers);
    GLFL_LOAD_FUNCTION(CreateProgramPipelines);
    GLFL_LOAD_FUNCTION(CreateQueries);
    GLFL_LOAD_FUNCTION(GetQueryBufferObjecti64v);
    GLFL_LOAD_FUNCTION(GetQueryBufferObjectiv);
    GLFL_LOAD_FUNCTION(GetQueryBufferObjectui64v);
    GLFL_LOAD_FUNCTION(GetQueryBufferObjectuiv);
}
void glfl::load_extension_GL_ARB_draw_buffers()
{
    GLFL_LOAD_FUNCTION(DrawBuffersARB);
}
void glfl::load_extension_GL_ARB_draw_buffers_blend()
{
    GLFL_LOAD_FUNCTION(BlendEquationiARB);
    GLFL_LOAD_FUNCTION(BlendEquationSeparateiARB);
    GLFL_LOAD_FUNCTION(BlendFunciARB);
    GLFL_LOAD_FUNCTION(BlendFuncSeparateiARB);
}
void glfl::load_extension_GL_ARB_draw_elements_base_vertex()
{
    GLFL_LOAD_FUNCTION(DrawElementsBaseVertex);
    GLFL_LOAD_FUNCTION(DrawRangeElementsBaseVertex);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertex);
    GLFL_LOAD_FUNCTION(MultiDrawElementsBaseVertex);
}
void glfl::load_extension_GL_ARB_draw_indirect()
{
    GLFL_LOAD_FUNCTION(DrawArraysIndirect);
    GLFL_LOAD_FUNCTION(DrawElementsIndirect);
}
void glfl::load_extension_GL_ARB_draw_instanced()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedARB);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedARB);
}
void glfl::load_extension_GL_ARB_enhanced_layouts() {}
void glfl::load_extension_GL_ARB_explicit_attrib_location() {}
void glfl::load_extension_GL_ARB_explicit_uniform_location() {}
void glfl::load_extension_GL_ARB_fragment_coord_conventions() {}
void glfl::load_extension_GL_ARB_fragment_layer_viewport() {}
void glfl::load_extension_GL_ARB_fragment_program()
{
    GLFL_LOAD_FUNCTION(ProgramStringARB);
    GLFL_LOAD_FUNCTION(BindProgramARB);
    GLFL_LOAD_FUNCTION(DeleteProgramsARB);
    GLFL_LOAD_FUNCTION(GenProgramsARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4dARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4dvARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4fARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4fvARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4dARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4dvARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4fARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4fvARB);
    GLFL_LOAD_FUNCTION(GetProgramEnvParameterdvARB);
    GLFL_LOAD_FUNCTION(GetProgramEnvParameterfvARB);
    GLFL_LOAD_FUNCTION(GetProgramLocalParameterdvARB);
    GLFL_LOAD_FUNCTION(GetProgramLocalParameterfvARB);
    GLFL_LOAD_FUNCTION(GetProgramivARB);
    GLFL_LOAD_FUNCTION(GetProgramStringARB);
    GLFL_LOAD_FUNCTION(IsProgramARB);
}
void glfl::load_extension_GL_ARB_fragment_program_shadow() {}
void glfl::load_extension_GL_ARB_fragment_shader() {}
void glfl::load_extension_GL_ARB_fragment_shader_interlock() {}
void glfl::load_extension_GL_ARB_framebuffer_no_attachments()
{
    GLFL_LOAD_FUNCTION(FramebufferParameteri);
    GLFL_LOAD_FUNCTION(GetFramebufferParameteriv);
}
void glfl::load_extension_GL_ARB_framebuffer_object()
{
    GLFL_LOAD_FUNCTION(IsRenderbuffer);
    GLFL_LOAD_FUNCTION(BindRenderbuffer);
    GLFL_LOAD_FUNCTION(DeleteRenderbuffers);
    GLFL_LOAD_FUNCTION(GenRenderbuffers);
    GLFL_LOAD_FUNCTION(RenderbufferStorage);
    GLFL_LOAD_FUNCTION(GetRenderbufferParameteriv);
    GLFL_LOAD_FUNCTION(IsFramebuffer);
    GLFL_LOAD_FUNCTION(BindFramebuffer);
    GLFL_LOAD_FUNCTION(DeleteFramebuffers);
    GLFL_LOAD_FUNCTION(GenFramebuffers);
    GLFL_LOAD_FUNCTION(CheckFramebufferStatus);
    GLFL_LOAD_FUNCTION(FramebufferTexture1D);
    GLFL_LOAD_FUNCTION(FramebufferTexture2D);
    GLFL_LOAD_FUNCTION(FramebufferTexture3D);
    GLFL_LOAD_FUNCTION(FramebufferRenderbuffer);
    GLFL_LOAD_FUNCTION(GetFramebufferAttachmentParameteriv);
    GLFL_LOAD_FUNCTION(GenerateMipmap);
    GLFL_LOAD_FUNCTION(BlitFramebuffer);
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisample);
    GLFL_LOAD_FUNCTION(FramebufferTextureLayer);
}
void glfl::load_extension_GL_ARB_framebuffer_sRGB() {}
void glfl::load_extension_GL_ARB_geometry_shader4()
{
    GLFL_LOAD_FUNCTION(ProgramParameteriARB);
    GLFL_LOAD_FUNCTION(FramebufferTextureARB);
    GLFL_LOAD_FUNCTION(FramebufferTextureLayerARB);
    GLFL_LOAD_FUNCTION(FramebufferTextureFaceARB);
}
void glfl::load_extension_GL_ARB_get_program_binary()
{
    GLFL_LOAD_FUNCTION(GetProgramBinary);
    GLFL_LOAD_FUNCTION(ProgramBinary);
    GLFL_LOAD_FUNCTION(ProgramParameteri);
}
void glfl::load_extension_GL_ARB_get_texture_sub_image()
{
    GLFL_LOAD_FUNCTION(GetTextureSubImage);
    GLFL_LOAD_FUNCTION(GetCompressedTextureSubImage);
}
void glfl::load_extension_GL_ARB_gpu_shader5() {}
void glfl::load_extension_GL_ARB_gpu_shader_fp64()
{
    GLFL_LOAD_FUNCTION(Uniform1d);
    GLFL_LOAD_FUNCTION(Uniform2d);
    GLFL_LOAD_FUNCTION(Uniform3d);
    GLFL_LOAD_FUNCTION(Uniform4d);
    GLFL_LOAD_FUNCTION(Uniform1dv);
    GLFL_LOAD_FUNCTION(Uniform2dv);
    GLFL_LOAD_FUNCTION(Uniform3dv);
    GLFL_LOAD_FUNCTION(Uniform4dv);
    GLFL_LOAD_FUNCTION(UniformMatrix2dv);
    GLFL_LOAD_FUNCTION(UniformMatrix3dv);
    GLFL_LOAD_FUNCTION(UniformMatrix4dv);
    GLFL_LOAD_FUNCTION(UniformMatrix2x3dv);
    GLFL_LOAD_FUNCTION(UniformMatrix2x4dv);
    GLFL_LOAD_FUNCTION(UniformMatrix3x2dv);
    GLFL_LOAD_FUNCTION(UniformMatrix3x4dv);
    GLFL_LOAD_FUNCTION(UniformMatrix4x2dv);
    GLFL_LOAD_FUNCTION(UniformMatrix4x3dv);
    GLFL_LOAD_FUNCTION(GetUniformdv);
}
void glfl::load_extension_GL_ARB_gpu_shader_int64()
{
    GLFL_LOAD_FUNCTION(Uniform1i64ARB);
    GLFL_LOAD_FUNCTION(Uniform2i64ARB);
    GLFL_LOAD_FUNCTION(Uniform3i64ARB);
    GLFL_LOAD_FUNCTION(Uniform4i64ARB);
    GLFL_LOAD_FUNCTION(Uniform1i64vARB);
    GLFL_LOAD_FUNCTION(Uniform2i64vARB);
    GLFL_LOAD_FUNCTION(Uniform3i64vARB);
    GLFL_LOAD_FUNCTION(Uniform4i64vARB);
    GLFL_LOAD_FUNCTION(Uniform1ui64ARB);
    GLFL_LOAD_FUNCTION(Uniform2ui64ARB);
    GLFL_LOAD_FUNCTION(Uniform3ui64ARB);
    GLFL_LOAD_FUNCTION(Uniform4ui64ARB);
    GLFL_LOAD_FUNCTION(Uniform1ui64vARB);
    GLFL_LOAD_FUNCTION(Uniform2ui64vARB);
    GLFL_LOAD_FUNCTION(Uniform3ui64vARB);
    GLFL_LOAD_FUNCTION(Uniform4ui64vARB);
    GLFL_LOAD_FUNCTION(GetUniformi64vARB);
    GLFL_LOAD_FUNCTION(GetUniformui64vARB);
    GLFL_LOAD_FUNCTION(GetnUniformi64vARB);
    GLFL_LOAD_FUNCTION(GetnUniformui64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform1i64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform2i64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform3i64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform4i64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform1i64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform2i64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform3i64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform4i64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui64vARB);
}
void glfl::load_extension_GL_ARB_half_float_pixel() {}
void glfl::load_extension_GL_ARB_half_float_vertex() {}
void glfl::load_extension_GL_ARB_imaging()
{
    GLFL_LOAD_FUNCTION(BlendColor);
    GLFL_LOAD_FUNCTION(BlendEquation);
    GLFL_LOAD_FUNCTION(ColorTable);
    GLFL_LOAD_FUNCTION(ColorTableParameterfv);
    GLFL_LOAD_FUNCTION(ColorTableParameteriv);
    GLFL_LOAD_FUNCTION(CopyColorTable);
    GLFL_LOAD_FUNCTION(GetColorTable);
    GLFL_LOAD_FUNCTION(GetColorTableParameterfv);
    GLFL_LOAD_FUNCTION(GetColorTableParameteriv);
    GLFL_LOAD_FUNCTION(ColorSubTable);
    GLFL_LOAD_FUNCTION(CopyColorSubTable);
    GLFL_LOAD_FUNCTION(ConvolutionFilter1D);
    GLFL_LOAD_FUNCTION(ConvolutionFilter2D);
    GLFL_LOAD_FUNCTION(ConvolutionParameterf);
    GLFL_LOAD_FUNCTION(ConvolutionParameterfv);
    GLFL_LOAD_FUNCTION(ConvolutionParameteri);
    GLFL_LOAD_FUNCTION(ConvolutionParameteriv);
    GLFL_LOAD_FUNCTION(CopyConvolutionFilter1D);
    GLFL_LOAD_FUNCTION(CopyConvolutionFilter2D);
    GLFL_LOAD_FUNCTION(GetConvolutionFilter);
    GLFL_LOAD_FUNCTION(GetConvolutionParameterfv);
    GLFL_LOAD_FUNCTION(GetConvolutionParameteriv);
    GLFL_LOAD_FUNCTION(GetSeparableFilter);
    GLFL_LOAD_FUNCTION(SeparableFilter2D);
    GLFL_LOAD_FUNCTION(GetHistogram);
    GLFL_LOAD_FUNCTION(GetHistogramParameterfv);
    GLFL_LOAD_FUNCTION(GetHistogramParameteriv);
    GLFL_LOAD_FUNCTION(GetMinmax);
    GLFL_LOAD_FUNCTION(GetMinmaxParameterfv);
    GLFL_LOAD_FUNCTION(GetMinmaxParameteriv);
    GLFL_LOAD_FUNCTION(Histogram);
    GLFL_LOAD_FUNCTION(Minmax);
    GLFL_LOAD_FUNCTION(ResetHistogram);
    GLFL_LOAD_FUNCTION(ResetMinmax);
}
void glfl::load_extension_GL_ARB_indirect_parameters()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysIndirectCountARB);
    GLFL_LOAD_FUNCTION(MultiDrawElementsIndirectCountARB);
}
void glfl::load_extension_GL_ARB_instanced_arrays()
{
    GLFL_LOAD_FUNCTION(VertexAttribDivisorARB);
}
void glfl::load_extension_GL_ARB_internalformat_query()
{
    GLFL_LOAD_FUNCTION(GetInternalformativ);
}
void glfl::load_extension_GL_ARB_internalformat_query2()
{
    GLFL_LOAD_FUNCTION(GetInternalformati64v);
}
void glfl::load_extension_GL_ARB_invalidate_subdata()
{
    GLFL_LOAD_FUNCTION(InvalidateTexSubImage);
    GLFL_LOAD_FUNCTION(InvalidateTexImage);
    GLFL_LOAD_FUNCTION(InvalidateBufferSubData);
    GLFL_LOAD_FUNCTION(InvalidateBufferData);
    GLFL_LOAD_FUNCTION(InvalidateFramebuffer);
    GLFL_LOAD_FUNCTION(InvalidateSubFramebuffer);
}
void glfl::load_extension_GL_ARB_map_buffer_alignment() {}
void glfl::load_extension_GL_ARB_map_buffer_range()
{
    GLFL_LOAD_FUNCTION(MapBufferRange);
    GLFL_LOAD_FUNCTION(FlushMappedBufferRange);
}
void glfl::load_extension_GL_ARB_matrix_palette()
{
    GLFL_LOAD_FUNCTION(CurrentPaletteMatrixARB);
    GLFL_LOAD_FUNCTION(MatrixIndexubvARB);
    GLFL_LOAD_FUNCTION(MatrixIndexusvARB);
    GLFL_LOAD_FUNCTION(MatrixIndexuivARB);
    GLFL_LOAD_FUNCTION(MatrixIndexPointerARB);
}
void glfl::load_extension_GL_ARB_multi_bind()
{
    GLFL_LOAD_FUNCTION(BindBuffersBase);
    GLFL_LOAD_FUNCTION(BindBuffersRange);
    GLFL_LOAD_FUNCTION(BindTextures);
    GLFL_LOAD_FUNCTION(BindSamplers);
    GLFL_LOAD_FUNCTION(BindImageTextures);
    GLFL_LOAD_FUNCTION(BindVertexBuffers);
}
void glfl::load_extension_GL_ARB_multi_draw_indirect()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysIndirect);
    GLFL_LOAD_FUNCTION(MultiDrawElementsIndirect);
}
void glfl::load_extension_GL_ARB_multisample()
{
    GLFL_LOAD_FUNCTION(SampleCoverageARB);
}
void glfl::load_extension_GL_ARB_multitexture()
{
    GLFL_LOAD_FUNCTION(ActiveTextureARB);
    GLFL_LOAD_FUNCTION(ClientActiveTextureARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1dARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1dvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1fARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1fvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1iARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1ivARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1sARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1svARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2dARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2dvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2fARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2fvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2iARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2ivARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2sARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2svARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3dARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3dvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3fARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3fvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3iARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3ivARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3sARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3svARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4dARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4dvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4fARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4fvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4iARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4ivARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4sARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4svARB);
}
void glfl::load_extension_GL_ARB_occlusion_query()
{
    GLFL_LOAD_FUNCTION(GenQueriesARB);
    GLFL_LOAD_FUNCTION(DeleteQueriesARB);
    GLFL_LOAD_FUNCTION(IsQueryARB);
    GLFL_LOAD_FUNCTION(BeginQueryARB);
    GLFL_LOAD_FUNCTION(EndQueryARB);
    GLFL_LOAD_FUNCTION(GetQueryivARB);
    GLFL_LOAD_FUNCTION(GetQueryObjectivARB);
    GLFL_LOAD_FUNCTION(GetQueryObjectuivARB);
}
void glfl::load_extension_GL_ARB_occlusion_query2() {}
void glfl::load_extension_GL_ARB_parallel_shader_compile()
{
    GLFL_LOAD_FUNCTION(MaxShaderCompilerThreadsARB);
}
void glfl::load_extension_GL_ARB_pipeline_statistics_query() {}
void glfl::load_extension_GL_ARB_pixel_buffer_object() {}
void glfl::load_extension_GL_ARB_point_parameters()
{
    GLFL_LOAD_FUNCTION(PointParameterfARB);
    GLFL_LOAD_FUNCTION(PointParameterfvARB);
}
void glfl::load_extension_GL_ARB_point_sprite() {}
void glfl::load_extension_GL_ARB_post_depth_coverage() {}
void glfl::load_extension_GL_ARB_program_interface_query()
{
    GLFL_LOAD_FUNCTION(GetProgramInterfaceiv);
    GLFL_LOAD_FUNCTION(GetProgramResourceIndex);
    GLFL_LOAD_FUNCTION(GetProgramResourceName);
    GLFL_LOAD_FUNCTION(GetProgramResourceiv);
    GLFL_LOAD_FUNCTION(GetProgramResourceLocation);
    GLFL_LOAD_FUNCTION(GetProgramResourceLocationIndex);
}
void glfl::load_extension_GL_ARB_provoking_vertex()
{
    GLFL_LOAD_FUNCTION(ProvokingVertex);
}
void glfl::load_extension_GL_ARB_query_buffer_object() {}
void glfl::load_extension_GL_ARB_robust_buffer_access_behavior() {}
void glfl::load_extension_GL_ARB_robustness()
{
    GLFL_LOAD_FUNCTION(GetGraphicsResetStatusARB);
    GLFL_LOAD_FUNCTION(GetnTexImageARB);
    GLFL_LOAD_FUNCTION(ReadnPixelsARB);
    GLFL_LOAD_FUNCTION(GetnCompressedTexImageARB);
    GLFL_LOAD_FUNCTION(GetnUniformfvARB);
    GLFL_LOAD_FUNCTION(GetnUniformivARB);
    GLFL_LOAD_FUNCTION(GetnUniformuivARB);
    GLFL_LOAD_FUNCTION(GetnUniformdvARB);
    GLFL_LOAD_FUNCTION(GetnMapdvARB);
    GLFL_LOAD_FUNCTION(GetnMapfvARB);
    GLFL_LOAD_FUNCTION(GetnMapivARB);
    GLFL_LOAD_FUNCTION(GetnPixelMapfvARB);
    GLFL_LOAD_FUNCTION(GetnPixelMapuivARB);
    GLFL_LOAD_FUNCTION(GetnPixelMapusvARB);
    GLFL_LOAD_FUNCTION(GetnPolygonStippleARB);
    GLFL_LOAD_FUNCTION(GetnColorTableARB);
    GLFL_LOAD_FUNCTION(GetnConvolutionFilterARB);
    GLFL_LOAD_FUNCTION(GetnSeparableFilterARB);
    GLFL_LOAD_FUNCTION(GetnHistogramARB);
    GLFL_LOAD_FUNCTION(GetnMinmaxARB);
}
void glfl::load_extension_GL_ARB_robustness_isolation() {}
void glfl::load_extension_GL_ARB_sample_locations()
{
    GLFL_LOAD_FUNCTION(FramebufferSampleLocationsfvARB);
    GLFL_LOAD_FUNCTION(NamedFramebufferSampleLocationsfvARB);
    GLFL_LOAD_FUNCTION(EvaluateDepthValuesARB);
}
void glfl::load_extension_GL_ARB_sample_shading()
{
    GLFL_LOAD_FUNCTION(MinSampleShadingARB);
}
void glfl::load_extension_GL_ARB_sampler_objects()
{
    GLFL_LOAD_FUNCTION(GenSamplers);
    GLFL_LOAD_FUNCTION(DeleteSamplers);
    GLFL_LOAD_FUNCTION(IsSampler);
    GLFL_LOAD_FUNCTION(BindSampler);
    GLFL_LOAD_FUNCTION(SamplerParameteri);
    GLFL_LOAD_FUNCTION(SamplerParameteriv);
    GLFL_LOAD_FUNCTION(SamplerParameterf);
    GLFL_LOAD_FUNCTION(SamplerParameterfv);
    GLFL_LOAD_FUNCTION(SamplerParameterIiv);
    GLFL_LOAD_FUNCTION(SamplerParameterIuiv);
    GLFL_LOAD_FUNCTION(GetSamplerParameteriv);
    GLFL_LOAD_FUNCTION(GetSamplerParameterIiv);
    GLFL_LOAD_FUNCTION(GetSamplerParameterfv);
    GLFL_LOAD_FUNCTION(GetSamplerParameterIuiv);
}
void glfl::load_extension_GL_ARB_seamless_cube_map() {}
void glfl::load_extension_GL_ARB_seamless_cubemap_per_texture() {}
void glfl::load_extension_GL_ARB_separate_shader_objects()
{
    GLFL_LOAD_FUNCTION(UseProgramStages);
    GLFL_LOAD_FUNCTION(ActiveShaderProgram);
    GLFL_LOAD_FUNCTION(CreateShaderProgramv);
    GLFL_LOAD_FUNCTION(BindProgramPipeline);
    GLFL_LOAD_FUNCTION(DeleteProgramPipelines);
    GLFL_LOAD_FUNCTION(GenProgramPipelines);
    GLFL_LOAD_FUNCTION(IsProgramPipeline);
    GLFL_LOAD_FUNCTION(GetProgramPipelineiv);
    GLFL_LOAD_FUNCTION(ProgramUniform1i);
    GLFL_LOAD_FUNCTION(ProgramUniform1iv);
    GLFL_LOAD_FUNCTION(ProgramUniform1f);
    GLFL_LOAD_FUNCTION(ProgramUniform1fv);
    GLFL_LOAD_FUNCTION(ProgramUniform1d);
    GLFL_LOAD_FUNCTION(ProgramUniform1dv);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui);
    GLFL_LOAD_FUNCTION(ProgramUniform1uiv);
    GLFL_LOAD_FUNCTION(ProgramUniform2i);
    GLFL_LOAD_FUNCTION(ProgramUniform2iv);
    GLFL_LOAD_FUNCTION(ProgramUniform2f);
    GLFL_LOAD_FUNCTION(ProgramUniform2fv);
    GLFL_LOAD_FUNCTION(ProgramUniform2d);
    GLFL_LOAD_FUNCTION(ProgramUniform2dv);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui);
    GLFL_LOAD_FUNCTION(ProgramUniform2uiv);
    GLFL_LOAD_FUNCTION(ProgramUniform3i);
    GLFL_LOAD_FUNCTION(ProgramUniform3iv);
    GLFL_LOAD_FUNCTION(ProgramUniform3f);
    GLFL_LOAD_FUNCTION(ProgramUniform3fv);
    GLFL_LOAD_FUNCTION(ProgramUniform3d);
    GLFL_LOAD_FUNCTION(ProgramUniform3dv);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui);
    GLFL_LOAD_FUNCTION(ProgramUniform3uiv);
    GLFL_LOAD_FUNCTION(ProgramUniform4i);
    GLFL_LOAD_FUNCTION(ProgramUniform4iv);
    GLFL_LOAD_FUNCTION(ProgramUniform4f);
    GLFL_LOAD_FUNCTION(ProgramUniform4fv);
    GLFL_LOAD_FUNCTION(ProgramUniform4d);
    GLFL_LOAD_FUNCTION(ProgramUniform4dv);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui);
    GLFL_LOAD_FUNCTION(ProgramUniform4uiv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3dv);
    GLFL_LOAD_FUNCTION(ValidateProgramPipeline);
    GLFL_LOAD_FUNCTION(GetProgramPipelineInfoLog);
}
void glfl::load_extension_GL_ARB_shader_atomic_counter_ops() {}
void glfl::load_extension_GL_ARB_shader_atomic_counters()
{
    GLFL_LOAD_FUNCTION(GetActiveAtomicCounterBufferiv);
}
void glfl::load_extension_GL_ARB_shader_ballot() {}
void glfl::load_extension_GL_ARB_shader_bit_encoding() {}
void glfl::load_extension_GL_ARB_shader_clock() {}
void glfl::load_extension_GL_ARB_shader_draw_parameters() {}
void glfl::load_extension_GL_ARB_shader_group_vote() {}
void glfl::load_extension_GL_ARB_shader_image_load_store()
{
    GLFL_LOAD_FUNCTION(BindImageTexture);
    GLFL_LOAD_FUNCTION(MemoryBarrier);
}
void glfl::load_extension_GL_ARB_shader_image_size() {}
void glfl::load_extension_GL_ARB_shader_objects()
{
    GLFL_LOAD_FUNCTION(DeleteObjectARB);
    GLFL_LOAD_FUNCTION(GetHandleARB);
    GLFL_LOAD_FUNCTION(DetachObjectARB);
    GLFL_LOAD_FUNCTION(CreateShaderObjectARB);
    GLFL_LOAD_FUNCTION(ShaderSourceARB);
    GLFL_LOAD_FUNCTION(CompileShaderARB);
    GLFL_LOAD_FUNCTION(CreateProgramObjectARB);
    GLFL_LOAD_FUNCTION(AttachObjectARB);
    GLFL_LOAD_FUNCTION(LinkProgramARB);
    GLFL_LOAD_FUNCTION(UseProgramObjectARB);
    GLFL_LOAD_FUNCTION(ValidateProgramARB);
    GLFL_LOAD_FUNCTION(Uniform1fARB);
    GLFL_LOAD_FUNCTION(Uniform2fARB);
    GLFL_LOAD_FUNCTION(Uniform3fARB);
    GLFL_LOAD_FUNCTION(Uniform4fARB);
    GLFL_LOAD_FUNCTION(Uniform1iARB);
    GLFL_LOAD_FUNCTION(Uniform2iARB);
    GLFL_LOAD_FUNCTION(Uniform3iARB);
    GLFL_LOAD_FUNCTION(Uniform4iARB);
    GLFL_LOAD_FUNCTION(Uniform1fvARB);
    GLFL_LOAD_FUNCTION(Uniform2fvARB);
    GLFL_LOAD_FUNCTION(Uniform3fvARB);
    GLFL_LOAD_FUNCTION(Uniform4fvARB);
    GLFL_LOAD_FUNCTION(Uniform1ivARB);
    GLFL_LOAD_FUNCTION(Uniform2ivARB);
    GLFL_LOAD_FUNCTION(Uniform3ivARB);
    GLFL_LOAD_FUNCTION(Uniform4ivARB);
    GLFL_LOAD_FUNCTION(UniformMatrix2fvARB);
    GLFL_LOAD_FUNCTION(UniformMatrix3fvARB);
    GLFL_LOAD_FUNCTION(UniformMatrix4fvARB);
    GLFL_LOAD_FUNCTION(GetObjectParameterfvARB);
    GLFL_LOAD_FUNCTION(GetObjectParameterivARB);
    GLFL_LOAD_FUNCTION(GetInfoLogARB);
    GLFL_LOAD_FUNCTION(GetAttachedObjectsARB);
    GLFL_LOAD_FUNCTION(GetUniformLocationARB);
    GLFL_LOAD_FUNCTION(GetActiveUniformARB);
    GLFL_LOAD_FUNCTION(GetUniformfvARB);
    GLFL_LOAD_FUNCTION(GetUniformivARB);
    GLFL_LOAD_FUNCTION(GetShaderSourceARB);
}
void glfl::load_extension_GL_ARB_shader_precision() {}
void glfl::load_extension_GL_ARB_shader_stencil_export() {}
void glfl::load_extension_GL_ARB_shader_storage_buffer_object()
{
    GLFL_LOAD_FUNCTION(ShaderStorageBlockBinding);
}
void glfl::load_extension_GL_ARB_shader_subroutine()
{
    GLFL_LOAD_FUNCTION(GetSubroutineUniformLocation);
    GLFL_LOAD_FUNCTION(GetSubroutineIndex);
    GLFL_LOAD_FUNCTION(GetActiveSubroutineUniformiv);
    GLFL_LOAD_FUNCTION(GetActiveSubroutineUniformName);
    GLFL_LOAD_FUNCTION(GetActiveSubroutineName);
    GLFL_LOAD_FUNCTION(UniformSubroutinesuiv);
    GLFL_LOAD_FUNCTION(GetUniformSubroutineuiv);
    GLFL_LOAD_FUNCTION(GetProgramStageiv);
}
void glfl::load_extension_GL_ARB_shader_texture_image_samples() {}
void glfl::load_extension_GL_ARB_shader_texture_lod() {}
void glfl::load_extension_GL_ARB_shader_viewport_layer_array() {}
void glfl::load_extension_GL_ARB_shading_language_100() {}
void glfl::load_extension_GL_ARB_shading_language_420pack() {}
void glfl::load_extension_GL_ARB_shading_language_include()
{
    GLFL_LOAD_FUNCTION(NamedStringARB);
    GLFL_LOAD_FUNCTION(DeleteNamedStringARB);
    GLFL_LOAD_FUNCTION(CompileShaderIncludeARB);
    GLFL_LOAD_FUNCTION(IsNamedStringARB);
    GLFL_LOAD_FUNCTION(GetNamedStringARB);
    GLFL_LOAD_FUNCTION(GetNamedStringivARB);
}
void glfl::load_extension_GL_ARB_shading_language_packing() {}
void glfl::load_extension_GL_ARB_shadow() {}
void glfl::load_extension_GL_ARB_shadow_ambient() {}
void glfl::load_extension_GL_ARB_sparse_buffer()
{
    GLFL_LOAD_FUNCTION(BufferPageCommitmentARB);
    GLFL_LOAD_FUNCTION(NamedBufferPageCommitmentEXT);
    GLFL_LOAD_FUNCTION(NamedBufferPageCommitmentARB);
}
void glfl::load_extension_GL_ARB_sparse_texture()
{
    GLFL_LOAD_FUNCTION(TexPageCommitmentARB);
}
void glfl::load_extension_GL_ARB_sparse_texture2() {}
void glfl::load_extension_GL_ARB_sparse_texture_clamp() {}
void glfl::load_extension_GL_ARB_stencil_texturing() {}
void glfl::load_extension_GL_ARB_sync()
{
    GLFL_LOAD_FUNCTION(FenceSync);
    GLFL_LOAD_FUNCTION(IsSync);
    GLFL_LOAD_FUNCTION(DeleteSync);
    GLFL_LOAD_FUNCTION(ClientWaitSync);
    GLFL_LOAD_FUNCTION(WaitSync);
    GLFL_LOAD_FUNCTION(GetInteger64v);
    GLFL_LOAD_FUNCTION(GetSynciv);
}
void glfl::load_extension_GL_ARB_tessellation_shader()
{
    GLFL_LOAD_FUNCTION(PatchParameteri);
    GLFL_LOAD_FUNCTION(PatchParameterfv);
}
void glfl::load_extension_GL_ARB_texture_barrier()
{
    GLFL_LOAD_FUNCTION(TextureBarrier);
}
void glfl::load_extension_GL_ARB_texture_border_clamp() {}
void glfl::load_extension_GL_ARB_texture_buffer_object()
{
    GLFL_LOAD_FUNCTION(TexBufferARB);
}
void glfl::load_extension_GL_ARB_texture_buffer_object_rgb32() {}
void glfl::load_extension_GL_ARB_texture_buffer_range()
{
    GLFL_LOAD_FUNCTION(TexBufferRange);
}
void glfl::load_extension_GL_ARB_texture_compression()
{
    GLFL_LOAD_FUNCTION(CompressedTexImage3DARB);
    GLFL_LOAD_FUNCTION(CompressedTexImage2DARB);
    GLFL_LOAD_FUNCTION(CompressedTexImage1DARB);
    GLFL_LOAD_FUNCTION(CompressedTexSubImage3DARB);
    GLFL_LOAD_FUNCTION(CompressedTexSubImage2DARB);
    GLFL_LOAD_FUNCTION(CompressedTexSubImage1DARB);
    GLFL_LOAD_FUNCTION(GetCompressedTexImageARB);
}
void glfl::load_extension_GL_ARB_texture_compression_bptc() {}
void glfl::load_extension_GL_ARB_texture_compression_rgtc() {}
void glfl::load_extension_GL_ARB_texture_cube_map() {}
void glfl::load_extension_GL_ARB_texture_cube_map_array() {}
void glfl::load_extension_GL_ARB_texture_env_add() {}
void glfl::load_extension_GL_ARB_texture_env_combine() {}
void glfl::load_extension_GL_ARB_texture_env_crossbar() {}
void glfl::load_extension_GL_ARB_texture_env_dot3() {}
void glfl::load_extension_GL_ARB_texture_filter_minmax() {}
void glfl::load_extension_GL_ARB_texture_float() {}
void glfl::load_extension_GL_ARB_texture_gather() {}
void glfl::load_extension_GL_ARB_texture_mirror_clamp_to_edge() {}
void glfl::load_extension_GL_ARB_texture_mirrored_repeat() {}
void glfl::load_extension_GL_ARB_texture_multisample()
{
    GLFL_LOAD_FUNCTION(TexImage2DMultisample);
    GLFL_LOAD_FUNCTION(TexImage3DMultisample);
    GLFL_LOAD_FUNCTION(GetMultisamplefv);
    GLFL_LOAD_FUNCTION(SampleMaski);
}
void glfl::load_extension_GL_ARB_texture_non_power_of_two() {}
void glfl::load_extension_GL_ARB_texture_query_levels() {}
void glfl::load_extension_GL_ARB_texture_query_lod() {}
void glfl::load_extension_GL_ARB_texture_rectangle() {}
void glfl::load_extension_GL_ARB_texture_rg() {}
void glfl::load_extension_GL_ARB_texture_rgb10_a2ui() {}
void glfl::load_extension_GL_ARB_texture_stencil8() {}
void glfl::load_extension_GL_ARB_texture_storage()
{
    GLFL_LOAD_FUNCTION(TexStorage1D);
    GLFL_LOAD_FUNCTION(TexStorage2D);
    GLFL_LOAD_FUNCTION(TexStorage3D);
}
void glfl::load_extension_GL_ARB_texture_storage_multisample()
{
    GLFL_LOAD_FUNCTION(TexStorage2DMultisample);
    GLFL_LOAD_FUNCTION(TexStorage3DMultisample);
}
void glfl::load_extension_GL_ARB_texture_swizzle() {}
void glfl::load_extension_GL_ARB_texture_view()
{
    GLFL_LOAD_FUNCTION(TextureView);
}
void glfl::load_extension_GL_ARB_timer_query()
{
    GLFL_LOAD_FUNCTION(QueryCounter);
    GLFL_LOAD_FUNCTION(GetQueryObjecti64v);
    GLFL_LOAD_FUNCTION(GetQueryObjectui64v);
}
void glfl::load_extension_GL_ARB_transform_feedback2()
{
    GLFL_LOAD_FUNCTION(BindTransformFeedback);
    GLFL_LOAD_FUNCTION(DeleteTransformFeedbacks);
    GLFL_LOAD_FUNCTION(GenTransformFeedbacks);
    GLFL_LOAD_FUNCTION(IsTransformFeedback);
    GLFL_LOAD_FUNCTION(PauseTransformFeedback);
    GLFL_LOAD_FUNCTION(ResumeTransformFeedback);
    GLFL_LOAD_FUNCTION(DrawTransformFeedback);
}
void glfl::load_extension_GL_ARB_transform_feedback3()
{
    GLFL_LOAD_FUNCTION(DrawTransformFeedbackStream);
    GLFL_LOAD_FUNCTION(BeginQueryIndexed);
    GLFL_LOAD_FUNCTION(EndQueryIndexed);
    GLFL_LOAD_FUNCTION(GetQueryIndexediv);
}
void glfl::load_extension_GL_ARB_transform_feedback_instanced()
{
    GLFL_LOAD_FUNCTION(DrawTransformFeedbackInstanced);
    GLFL_LOAD_FUNCTION(DrawTransformFeedbackStreamInstanced);
}
void glfl::load_extension_GL_ARB_transform_feedback_overflow_query() {}
void glfl::load_extension_GL_ARB_transpose_matrix()
{
    GLFL_LOAD_FUNCTION(LoadTransposeMatrixfARB);
    GLFL_LOAD_FUNCTION(LoadTransposeMatrixdARB);
    GLFL_LOAD_FUNCTION(MultTransposeMatrixfARB);
    GLFL_LOAD_FUNCTION(MultTransposeMatrixdARB);
}
void glfl::load_extension_GL_ARB_uniform_buffer_object()
{
    GLFL_LOAD_FUNCTION(GetUniformIndices);
    GLFL_LOAD_FUNCTION(GetActiveUniformsiv);
    GLFL_LOAD_FUNCTION(GetActiveUniformName);
    GLFL_LOAD_FUNCTION(GetUniformBlockIndex);
    GLFL_LOAD_FUNCTION(GetActiveUniformBlockiv);
    GLFL_LOAD_FUNCTION(GetActiveUniformBlockName);
    GLFL_LOAD_FUNCTION(UniformBlockBinding);
    GLFL_LOAD_FUNCTION(BindBufferRange);
    GLFL_LOAD_FUNCTION(BindBufferBase);
    GLFL_LOAD_FUNCTION(GetIntegeri_v);
}
void glfl::load_extension_GL_ARB_vertex_array_bgra() {}
void glfl::load_extension_GL_ARB_vertex_array_object()
{
    GLFL_LOAD_FUNCTION(BindVertexArray);
    GLFL_LOAD_FUNCTION(DeleteVertexArrays);
    GLFL_LOAD_FUNCTION(GenVertexArrays);
    GLFL_LOAD_FUNCTION(IsVertexArray);
}
void glfl::load_extension_GL_ARB_vertex_attrib_64bit()
{
    GLFL_LOAD_FUNCTION(VertexAttribL1d);
    GLFL_LOAD_FUNCTION(VertexAttribL2d);
    GLFL_LOAD_FUNCTION(VertexAttribL3d);
    GLFL_LOAD_FUNCTION(VertexAttribL4d);
    GLFL_LOAD_FUNCTION(VertexAttribL1dv);
    GLFL_LOAD_FUNCTION(VertexAttribL2dv);
    GLFL_LOAD_FUNCTION(VertexAttribL3dv);
    GLFL_LOAD_FUNCTION(VertexAttribL4dv);
    GLFL_LOAD_FUNCTION(VertexAttribLPointer);
    GLFL_LOAD_FUNCTION(GetVertexAttribLdv);
}
void glfl::load_extension_GL_ARB_vertex_attrib_binding()
{
    GLFL_LOAD_FUNCTION(BindVertexBuffer);
    GLFL_LOAD_FUNCTION(VertexAttribFormat);
    GLFL_LOAD_FUNCTION(VertexAttribIFormat);
    GLFL_LOAD_FUNCTION(VertexAttribLFormat);
    GLFL_LOAD_FUNCTION(VertexAttribBinding);
    GLFL_LOAD_FUNCTION(VertexBindingDivisor);
}
void glfl::load_extension_GL_ARB_vertex_blend()
{
    GLFL_LOAD_FUNCTION(WeightbvARB);
    GLFL_LOAD_FUNCTION(WeightsvARB);
    GLFL_LOAD_FUNCTION(WeightivARB);
    GLFL_LOAD_FUNCTION(WeightfvARB);
    GLFL_LOAD_FUNCTION(WeightdvARB);
    GLFL_LOAD_FUNCTION(WeightubvARB);
    GLFL_LOAD_FUNCTION(WeightusvARB);
    GLFL_LOAD_FUNCTION(WeightuivARB);
    GLFL_LOAD_FUNCTION(WeightPointerARB);
    GLFL_LOAD_FUNCTION(VertexBlendARB);
}
void glfl::load_extension_GL_ARB_vertex_buffer_object()
{
    GLFL_LOAD_FUNCTION(BindBufferARB);
    GLFL_LOAD_FUNCTION(DeleteBuffersARB);
    GLFL_LOAD_FUNCTION(GenBuffersARB);
    GLFL_LOAD_FUNCTION(IsBufferARB);
    GLFL_LOAD_FUNCTION(BufferDataARB);
    GLFL_LOAD_FUNCTION(BufferSubDataARB);
    GLFL_LOAD_FUNCTION(GetBufferSubDataARB);
    GLFL_LOAD_FUNCTION(MapBufferARB);
    GLFL_LOAD_FUNCTION(UnmapBufferARB);
    GLFL_LOAD_FUNCTION(GetBufferParameterivARB);
    GLFL_LOAD_FUNCTION(GetBufferPointervARB);
}
void glfl::load_extension_GL_ARB_vertex_program()
{
    GLFL_LOAD_FUNCTION(VertexAttrib1dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NbvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NsvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NubARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NubvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NuivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NusvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4bvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4ivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4ubvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4uivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4usvARB);
    GLFL_LOAD_FUNCTION(VertexAttribPointerARB);
    GLFL_LOAD_FUNCTION(EnableVertexAttribArrayARB);
    GLFL_LOAD_FUNCTION(DisableVertexAttribArrayARB);
    GLFL_LOAD_FUNCTION(ProgramStringARB);
    GLFL_LOAD_FUNCTION(BindProgramARB);
    GLFL_LOAD_FUNCTION(DeleteProgramsARB);
    GLFL_LOAD_FUNCTION(GenProgramsARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4dARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4dvARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4fARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4fvARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4dARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4dvARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4fARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4fvARB);
    GLFL_LOAD_FUNCTION(GetProgramEnvParameterdvARB);
    GLFL_LOAD_FUNCTION(GetProgramEnvParameterfvARB);
    GLFL_LOAD_FUNCTION(GetProgramLocalParameterdvARB);
    GLFL_LOAD_FUNCTION(GetProgramLocalParameterfvARB);
    GLFL_LOAD_FUNCTION(GetProgramivARB);
    GLFL_LOAD_FUNCTION(GetProgramStringARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribdvARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribfvARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribivARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribPointervARB);
    GLFL_LOAD_FUNCTION(IsProgramARB);
}
void glfl::load_extension_GL_ARB_vertex_shader()
{
    GLFL_LOAD_FUNCTION(VertexAttrib1fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NubARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4ivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4bvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4ubvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4usvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4uivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NbvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NsvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NubvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NusvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NuivARB);
    GLFL_LOAD_FUNCTION(VertexAttribPointerARB);
    GLFL_LOAD_FUNCTION(EnableVertexAttribArrayARB);
    GLFL_LOAD_FUNCTION(DisableVertexAttribArrayARB);
    GLFL_LOAD_FUNCTION(BindAttribLocationARB);
    GLFL_LOAD_FUNCTION(GetActiveAttribARB);
    GLFL_LOAD_FUNCTION(GetAttribLocationARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribdvARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribfvARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribivARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribPointervARB);
}
void glfl::load_extension_GL_ARB_vertex_type_10f_11f_11f_rev() {}
void glfl::load_extension_GL_ARB_vertex_type_2_10_10_10_rev()
{
    GLFL_LOAD_FUNCTION(VertexAttribP1ui);
    GLFL_LOAD_FUNCTION(VertexAttribP1uiv);
    GLFL_LOAD_FUNCTION(VertexAttribP2ui);
    GLFL_LOAD_FUNCTION(VertexAttribP2uiv);
    GLFL_LOAD_FUNCTION(VertexAttribP3ui);
    GLFL_LOAD_FUNCTION(VertexAttribP3uiv);
    GLFL_LOAD_FUNCTION(VertexAttribP4ui);
    GLFL_LOAD_FUNCTION(VertexAttribP4uiv);
    GLFL_LOAD_FUNCTION(VertexP2ui);
    GLFL_LOAD_FUNCTION(VertexP2uiv);
    GLFL_LOAD_FUNCTION(VertexP3ui);
    GLFL_LOAD_FUNCTION(VertexP3uiv);
    GLFL_LOAD_FUNCTION(VertexP4ui);
    GLFL_LOAD_FUNCTION(VertexP4uiv);
    GLFL_LOAD_FUNCTION(TexCoordP1ui);
    GLFL_LOAD_FUNCTION(TexCoordP1uiv);
    GLFL_LOAD_FUNCTION(TexCoordP2ui);
    GLFL_LOAD_FUNCTION(TexCoordP2uiv);
    GLFL_LOAD_FUNCTION(TexCoordP3ui);
    GLFL_LOAD_FUNCTION(TexCoordP3uiv);
    GLFL_LOAD_FUNCTION(TexCoordP4ui);
    GLFL_LOAD_FUNCTION(TexCoordP4uiv);
    GLFL_LOAD_FUNCTION(MultiTexCoordP1ui);
    GLFL_LOAD_FUNCTION(MultiTexCoordP1uiv);
    GLFL_LOAD_FUNCTION(MultiTexCoordP2ui);
    GLFL_LOAD_FUNCTION(MultiTexCoordP2uiv);
    GLFL_LOAD_FUNCTION(MultiTexCoordP3ui);
    GLFL_LOAD_FUNCTION(MultiTexCoordP3uiv);
    GLFL_LOAD_FUNCTION(MultiTexCoordP4ui);
    GLFL_LOAD_FUNCTION(MultiTexCoordP4uiv);
    GLFL_LOAD_FUNCTION(NormalP3ui);
    GLFL_LOAD_FUNCTION(NormalP3uiv);
    GLFL_LOAD_FUNCTION(ColorP3ui);
    GLFL_LOAD_FUNCTION(ColorP3uiv);
    GLFL_LOAD_FUNCTION(ColorP4ui);
    GLFL_LOAD_FUNCTION(ColorP4uiv);
    GLFL_LOAD_FUNCTION(SecondaryColorP3ui);
    GLFL_LOAD_FUNCTION(SecondaryColorP3uiv);
}
void glfl::load_extension_GL_ARB_viewport_array()
{
    GLFL_LOAD_FUNCTION(ViewportArrayv);
    GLFL_LOAD_FUNCTION(ViewportIndexedf);
    GLFL_LOAD_FUNCTION(ViewportIndexedfv);
    GLFL_LOAD_FUNCTION(ScissorArrayv);
    GLFL_LOAD_FUNCTION(ScissorIndexed);
    GLFL_LOAD_FUNCTION(ScissorIndexedv);
    GLFL_LOAD_FUNCTION(DepthRangeArrayv);
    GLFL_LOAD_FUNCTION(DepthRangeIndexed);
    GLFL_LOAD_FUNCTION(GetFloati_v);
    GLFL_LOAD_FUNCTION(GetDoublei_v);
}
void glfl::load_extension_GL_ARB_window_pos()
{
    GLFL_LOAD_FUNCTION(WindowPos2dARB);
    GLFL_LOAD_FUNCTION(WindowPos2dvARB);
    GLFL_LOAD_FUNCTION(WindowPos2fARB);
    GLFL_LOAD_FUNCTION(WindowPos2fvARB);
    GLFL_LOAD_FUNCTION(WindowPos2iARB);
    GLFL_LOAD_FUNCTION(WindowPos2ivARB);
    GLFL_LOAD_FUNCTION(WindowPos2sARB);
    GLFL_LOAD_FUNCTION(WindowPos2svARB);
    GLFL_LOAD_FUNCTION(WindowPos3dARB);
    GLFL_LOAD_FUNCTION(WindowPos3dvARB);
    GLFL_LOAD_FUNCTION(WindowPos3fARB);
    GLFL_LOAD_FUNCTION(WindowPos3fvARB);
    GLFL_LOAD_FUNCTION(WindowPos3iARB);
    GLFL_LOAD_FUNCTION(WindowPos3ivARB);
    GLFL_LOAD_FUNCTION(WindowPos3sARB);
    GLFL_LOAD_FUNCTION(WindowPos3svARB);
}
void glfl::load_extension_GL_ARM_mali_program_binary() {}
void glfl::load_extension_GL_ARM_mali_shader_binary() {}
void glfl::load_extension_GL_ARM_rgba8() {}
void glfl::load_extension_GL_ARM_shader_framebuffer_fetch() {}
void glfl::load_extension_GL_ARM_shader_framebuffer_fetch_depth_stencil() {}
void glfl::load_extension_GL_ATI_draw_buffers()
{
    GLFL_LOAD_FUNCTION(DrawBuffersATI);
}
void glfl::load_extension_GL_ATI_element_array()
{
    GLFL_LOAD_FUNCTION(ElementPointerATI);
    GLFL_LOAD_FUNCTION(DrawElementArrayATI);
    GLFL_LOAD_FUNCTION(DrawRangeElementArrayATI);
}
void glfl::load_extension_GL_ATI_envmap_bumpmap()
{
    GLFL_LOAD_FUNCTION(TexBumpParameterivATI);
    GLFL_LOAD_FUNCTION(TexBumpParameterfvATI);
    GLFL_LOAD_FUNCTION(GetTexBumpParameterivATI);
    GLFL_LOAD_FUNCTION(GetTexBumpParameterfvATI);
}
void glfl::load_extension_GL_ATI_fragment_shader()
{
    GLFL_LOAD_FUNCTION(GenFragmentShadersATI);
    GLFL_LOAD_FUNCTION(BindFragmentShaderATI);
    GLFL_LOAD_FUNCTION(DeleteFragmentShaderATI);
    GLFL_LOAD_FUNCTION(BeginFragmentShaderATI);
    GLFL_LOAD_FUNCTION(EndFragmentShaderATI);
    GLFL_LOAD_FUNCTION(PassTexCoordATI);
    GLFL_LOAD_FUNCTION(SampleMapATI);
    GLFL_LOAD_FUNCTION(ColorFragmentOp1ATI);
    GLFL_LOAD_FUNCTION(ColorFragmentOp2ATI);
    GLFL_LOAD_FUNCTION(ColorFragmentOp3ATI);
    GLFL_LOAD_FUNCTION(AlphaFragmentOp1ATI);
    GLFL_LOAD_FUNCTION(AlphaFragmentOp2ATI);
    GLFL_LOAD_FUNCTION(AlphaFragmentOp3ATI);
    GLFL_LOAD_FUNCTION(SetFragmentShaderConstantATI);
}
void glfl::load_extension_GL_ATI_map_object_buffer()
{
    GLFL_LOAD_FUNCTION(MapObjectBufferATI);
    GLFL_LOAD_FUNCTION(UnmapObjectBufferATI);
}
void glfl::load_extension_GL_ATI_meminfo() {}
void glfl::load_extension_GL_ATI_pixel_format_float() {}
void glfl::load_extension_GL_ATI_pn_triangles()
{
    GLFL_LOAD_FUNCTION(PNTrianglesiATI);
    GLFL_LOAD_FUNCTION(PNTrianglesfATI);
}
void glfl::load_extension_GL_ATI_separate_stencil()
{
    GLFL_LOAD_FUNCTION(StencilOpSeparateATI);
    GLFL_LOAD_FUNCTION(StencilFuncSeparateATI);
}
void glfl::load_extension_GL_ATI_text_fragment_shader() {}
void glfl::load_extension_GL_ATI_texture_env_combine3() {}
void glfl::load_extension_GL_ATI_texture_float() {}
void glfl::load_extension_GL_ATI_texture_mirror_once() {}
void glfl::load_extension_GL_ATI_vertex_array_object()
{
    GLFL_LOAD_FUNCTION(NewObjectBufferATI);
    GLFL_LOAD_FUNCTION(IsObjectBufferATI);
    GLFL_LOAD_FUNCTION(UpdateObjectBufferATI);
    GLFL_LOAD_FUNCTION(GetObjectBufferfvATI);
    GLFL_LOAD_FUNCTION(GetObjectBufferivATI);
    GLFL_LOAD_FUNCTION(FreeObjectBufferATI);
    GLFL_LOAD_FUNCTION(ArrayObjectATI);
    GLFL_LOAD_FUNCTION(GetArrayObjectfvATI);
    GLFL_LOAD_FUNCTION(GetArrayObjectivATI);
    GLFL_LOAD_FUNCTION(VariantArrayObjectATI);
    GLFL_LOAD_FUNCTION(GetVariantArrayObjectfvATI);
    GLFL_LOAD_FUNCTION(GetVariantArrayObjectivATI);
}
void glfl::load_extension_GL_ATI_vertex_attrib_array_object()
{
    GLFL_LOAD_FUNCTION(VertexAttribArrayObjectATI);
    GLFL_LOAD_FUNCTION(GetVertexAttribArrayObjectfvATI);
    GLFL_LOAD_FUNCTION(GetVertexAttribArrayObjectivATI);
}
void glfl::load_extension_GL_ATI_vertex_streams()
{
    GLFL_LOAD_FUNCTION(VertexStream1sATI);
    GLFL_LOAD_FUNCTION(VertexStream1svATI);
    GLFL_LOAD_FUNCTION(VertexStream1iATI);
    GLFL_LOAD_FUNCTION(VertexStream1ivATI);
    GLFL_LOAD_FUNCTION(VertexStream1fATI);
    GLFL_LOAD_FUNCTION(VertexStream1fvATI);
    GLFL_LOAD_FUNCTION(VertexStream1dATI);
    GLFL_LOAD_FUNCTION(VertexStream1dvATI);
    GLFL_LOAD_FUNCTION(VertexStream2sATI);
    GLFL_LOAD_FUNCTION(VertexStream2svATI);
    GLFL_LOAD_FUNCTION(VertexStream2iATI);
    GLFL_LOAD_FUNCTION(VertexStream2ivATI);
    GLFL_LOAD_FUNCTION(VertexStream2fATI);
    GLFL_LOAD_FUNCTION(VertexStream2fvATI);
    GLFL_LOAD_FUNCTION(VertexStream2dATI);
    GLFL_LOAD_FUNCTION(VertexStream2dvATI);
    GLFL_LOAD_FUNCTION(VertexStream3sATI);
    GLFL_LOAD_FUNCTION(VertexStream3svATI);
    GLFL_LOAD_FUNCTION(VertexStream3iATI);
    GLFL_LOAD_FUNCTION(VertexStream3ivATI);
    GLFL_LOAD_FUNCTION(VertexStream3fATI);
    GLFL_LOAD_FUNCTION(VertexStream3fvATI);
    GLFL_LOAD_FUNCTION(VertexStream3dATI);
    GLFL_LOAD_FUNCTION(VertexStream3dvATI);
    GLFL_LOAD_FUNCTION(VertexStream4sATI);
    GLFL_LOAD_FUNCTION(VertexStream4svATI);
    GLFL_LOAD_FUNCTION(VertexStream4iATI);
    GLFL_LOAD_FUNCTION(VertexStream4ivATI);
    GLFL_LOAD_FUNCTION(VertexStream4fATI);
    GLFL_LOAD_FUNCTION(VertexStream4fvATI);
    GLFL_LOAD_FUNCTION(VertexStream4dATI);
    GLFL_LOAD_FUNCTION(VertexStream4dvATI);
    GLFL_LOAD_FUNCTION(NormalStream3bATI);
    GLFL_LOAD_FUNCTION(NormalStream3bvATI);
    GLFL_LOAD_FUNCTION(NormalStream3sATI);
    GLFL_LOAD_FUNCTION(NormalStream3svATI);
    GLFL_LOAD_FUNCTION(NormalStream3iATI);
    GLFL_LOAD_FUNCTION(NormalStream3ivATI);
    GLFL_LOAD_FUNCTION(NormalStream3fATI);
    GLFL_LOAD_FUNCTION(NormalStream3fvATI);
    GLFL_LOAD_FUNCTION(NormalStream3dATI);
    GLFL_LOAD_FUNCTION(NormalStream3dvATI);
    GLFL_LOAD_FUNCTION(ClientActiveVertexStreamATI);
    GLFL_LOAD_FUNCTION(VertexBlendEnviATI);
    GLFL_LOAD_FUNCTION(VertexBlendEnvfATI);
}
void glfl::load_extension_GL_DMP_program_binary() {}
void glfl::load_extension_GL_DMP_shader_binary() {}
void glfl::load_extension_GL_EXT_422_pixels() {}
void glfl::load_extension_GL_EXT_YUV_target() {}
void glfl::load_extension_GL_EXT_abgr() {}
void glfl::load_extension_GL_EXT_base_instance()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedBaseInstanceEXT);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseInstanceEXT);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertexBaseInstanceEXT);
}
void glfl::load_extension_GL_EXT_bgra() {}
void glfl::load_extension_GL_EXT_bindable_uniform()
{
    GLFL_LOAD_FUNCTION(UniformBufferEXT);
    GLFL_LOAD_FUNCTION(GetUniformBufferSizeEXT);
    GLFL_LOAD_FUNCTION(GetUniformOffsetEXT);
}
void glfl::load_extension_GL_EXT_blend_color()
{
    GLFL_LOAD_FUNCTION(BlendColorEXT);
}
void glfl::load_extension_GL_EXT_blend_equation_separate()
{
    GLFL_LOAD_FUNCTION(BlendEquationSeparateEXT);
}
void glfl::load_extension_GL_EXT_blend_func_extended()
{
    GLFL_LOAD_FUNCTION(BindFragDataLocationIndexedEXT);
    GLFL_LOAD_FUNCTION(BindFragDataLocationEXT);
    GLFL_LOAD_FUNCTION(GetProgramResourceLocationIndexEXT);
    GLFL_LOAD_FUNCTION(GetFragDataIndexEXT);
}
void glfl::load_extension_GL_EXT_blend_func_separate()
{
    GLFL_LOAD_FUNCTION(BlendFuncSeparateEXT);
}
void glfl::load_extension_GL_EXT_blend_logic_op() {}
void glfl::load_extension_GL_EXT_blend_minmax()
{
    GLFL_LOAD_FUNCTION(BlendEquationEXT);
}
void glfl::load_extension_GL_EXT_blend_subtract() {}
void glfl::load_extension_GL_EXT_buffer_storage()
{
    GLFL_LOAD_FUNCTION(BufferStorageEXT);
}
void glfl::load_extension_GL_EXT_clear_texture()
{
    GLFL_LOAD_FUNCTION(ClearTexImageEXT);
    GLFL_LOAD_FUNCTION(ClearTexSubImageEXT);
}
void glfl::load_extension_GL_EXT_clip_cull_distance() {}
void glfl::load_extension_GL_EXT_clip_volume_hint() {}
void glfl::load_extension_GL_EXT_cmyka() {}
void glfl::load_extension_GL_EXT_color_buffer_float() {}
void glfl::load_extension_GL_EXT_color_buffer_half_float() {}
void glfl::load_extension_GL_EXT_color_subtable()
{
    GLFL_LOAD_FUNCTION(ColorSubTableEXT);
    GLFL_LOAD_FUNCTION(CopyColorSubTableEXT);
}
void glfl::load_extension_GL_EXT_compiled_vertex_array()
{
    GLFL_LOAD_FUNCTION(LockArraysEXT);
    GLFL_LOAD_FUNCTION(UnlockArraysEXT);
}
void glfl::load_extension_GL_EXT_conservative_depth() {}
void glfl::load_extension_GL_EXT_convolution()
{
    GLFL_LOAD_FUNCTION(ConvolutionFilter1DEXT);
    GLFL_LOAD_FUNCTION(ConvolutionFilter2DEXT);
    GLFL_LOAD_FUNCTION(ConvolutionParameterfEXT);
    GLFL_LOAD_FUNCTION(ConvolutionParameterfvEXT);
    GLFL_LOAD_FUNCTION(ConvolutionParameteriEXT);
    GLFL_LOAD_FUNCTION(ConvolutionParameterivEXT);
    GLFL_LOAD_FUNCTION(CopyConvolutionFilter1DEXT);
    GLFL_LOAD_FUNCTION(CopyConvolutionFilter2DEXT);
    GLFL_LOAD_FUNCTION(GetConvolutionFilterEXT);
    GLFL_LOAD_FUNCTION(GetConvolutionParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetConvolutionParameterivEXT);
    GLFL_LOAD_FUNCTION(GetSeparableFilterEXT);
    GLFL_LOAD_FUNCTION(SeparableFilter2DEXT);
}
void glfl::load_extension_GL_EXT_coordinate_frame()
{
    GLFL_LOAD_FUNCTION(Tangent3bEXT);
    GLFL_LOAD_FUNCTION(Tangent3bvEXT);
    GLFL_LOAD_FUNCTION(Tangent3dEXT);
    GLFL_LOAD_FUNCTION(Tangent3dvEXT);
    GLFL_LOAD_FUNCTION(Tangent3fEXT);
    GLFL_LOAD_FUNCTION(Tangent3fvEXT);
    GLFL_LOAD_FUNCTION(Tangent3iEXT);
    GLFL_LOAD_FUNCTION(Tangent3ivEXT);
    GLFL_LOAD_FUNCTION(Tangent3sEXT);
    GLFL_LOAD_FUNCTION(Tangent3svEXT);
    GLFL_LOAD_FUNCTION(Binormal3bEXT);
    GLFL_LOAD_FUNCTION(Binormal3bvEXT);
    GLFL_LOAD_FUNCTION(Binormal3dEXT);
    GLFL_LOAD_FUNCTION(Binormal3dvEXT);
    GLFL_LOAD_FUNCTION(Binormal3fEXT);
    GLFL_LOAD_FUNCTION(Binormal3fvEXT);
    GLFL_LOAD_FUNCTION(Binormal3iEXT);
    GLFL_LOAD_FUNCTION(Binormal3ivEXT);
    GLFL_LOAD_FUNCTION(Binormal3sEXT);
    GLFL_LOAD_FUNCTION(Binormal3svEXT);
    GLFL_LOAD_FUNCTION(TangentPointerEXT);
    GLFL_LOAD_FUNCTION(BinormalPointerEXT);
}
void glfl::load_extension_GL_EXT_copy_image()
{
    GLFL_LOAD_FUNCTION(CopyImageSubDataEXT);
}
void glfl::load_extension_GL_EXT_copy_texture()
{
    GLFL_LOAD_FUNCTION(CopyTexImage1DEXT);
    GLFL_LOAD_FUNCTION(CopyTexImage2DEXT);
    GLFL_LOAD_FUNCTION(CopyTexSubImage1DEXT);
    GLFL_LOAD_FUNCTION(CopyTexSubImage2DEXT);
    GLFL_LOAD_FUNCTION(CopyTexSubImage3DEXT);
}
void glfl::load_extension_GL_EXT_cull_vertex()
{
    GLFL_LOAD_FUNCTION(CullParameterdvEXT);
    GLFL_LOAD_FUNCTION(CullParameterfvEXT);
}
void glfl::load_extension_GL_EXT_debug_label()
{
    GLFL_LOAD_FUNCTION(LabelObjectEXT);
    GLFL_LOAD_FUNCTION(GetObjectLabelEXT);
}
void glfl::load_extension_GL_EXT_debug_marker()
{
    GLFL_LOAD_FUNCTION(InsertEventMarkerEXT);
    GLFL_LOAD_FUNCTION(PushGroupMarkerEXT);
    GLFL_LOAD_FUNCTION(PopGroupMarkerEXT);
}
void glfl::load_extension_GL_EXT_depth_bounds_test()
{
    GLFL_LOAD_FUNCTION(DepthBoundsEXT);
}
void glfl::load_extension_GL_EXT_direct_state_access()
{
    GLFL_LOAD_FUNCTION(MatrixLoadfEXT);
    GLFL_LOAD_FUNCTION(MatrixLoaddEXT);
    GLFL_LOAD_FUNCTION(MatrixMultfEXT);
    GLFL_LOAD_FUNCTION(MatrixMultdEXT);
    GLFL_LOAD_FUNCTION(MatrixLoadIdentityEXT);
    GLFL_LOAD_FUNCTION(MatrixRotatefEXT);
    GLFL_LOAD_FUNCTION(MatrixRotatedEXT);
    GLFL_LOAD_FUNCTION(MatrixScalefEXT);
    GLFL_LOAD_FUNCTION(MatrixScaledEXT);
    GLFL_LOAD_FUNCTION(MatrixTranslatefEXT);
    GLFL_LOAD_FUNCTION(MatrixTranslatedEXT);
    GLFL_LOAD_FUNCTION(MatrixFrustumEXT);
    GLFL_LOAD_FUNCTION(MatrixOrthoEXT);
    GLFL_LOAD_FUNCTION(MatrixPopEXT);
    GLFL_LOAD_FUNCTION(MatrixPushEXT);
    GLFL_LOAD_FUNCTION(ClientAttribDefaultEXT);
    GLFL_LOAD_FUNCTION(PushClientAttribDefaultEXT);
    GLFL_LOAD_FUNCTION(TextureParameterfEXT);
    GLFL_LOAD_FUNCTION(TextureParameterfvEXT);
    GLFL_LOAD_FUNCTION(TextureParameteriEXT);
    GLFL_LOAD_FUNCTION(TextureParameterivEXT);
    GLFL_LOAD_FUNCTION(TextureImage1DEXT);
    GLFL_LOAD_FUNCTION(TextureImage2DEXT);
    GLFL_LOAD_FUNCTION(TextureSubImage1DEXT);
    GLFL_LOAD_FUNCTION(TextureSubImage2DEXT);
    GLFL_LOAD_FUNCTION(CopyTextureImage1DEXT);
    GLFL_LOAD_FUNCTION(CopyTextureImage2DEXT);
    GLFL_LOAD_FUNCTION(CopyTextureSubImage1DEXT);
    GLFL_LOAD_FUNCTION(CopyTextureSubImage2DEXT);
    GLFL_LOAD_FUNCTION(GetTextureImageEXT);
    GLFL_LOAD_FUNCTION(GetTextureParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetTextureParameterivEXT);
    GLFL_LOAD_FUNCTION(GetTextureLevelParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetTextureLevelParameterivEXT);
    GLFL_LOAD_FUNCTION(TextureImage3DEXT);
    GLFL_LOAD_FUNCTION(TextureSubImage3DEXT);
    GLFL_LOAD_FUNCTION(CopyTextureSubImage3DEXT);
    GLFL_LOAD_FUNCTION(BindMultiTextureEXT);
    GLFL_LOAD_FUNCTION(MultiTexCoordPointerEXT);
    GLFL_LOAD_FUNCTION(MultiTexEnvfEXT);
    GLFL_LOAD_FUNCTION(MultiTexEnvfvEXT);
    GLFL_LOAD_FUNCTION(MultiTexEnviEXT);
    GLFL_LOAD_FUNCTION(MultiTexEnvivEXT);
    GLFL_LOAD_FUNCTION(MultiTexGendEXT);
    GLFL_LOAD_FUNCTION(MultiTexGendvEXT);
    GLFL_LOAD_FUNCTION(MultiTexGenfEXT);
    GLFL_LOAD_FUNCTION(MultiTexGenfvEXT);
    GLFL_LOAD_FUNCTION(MultiTexGeniEXT);
    GLFL_LOAD_FUNCTION(MultiTexGenivEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexEnvfvEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexEnvivEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexGendvEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexGenfvEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexGenivEXT);
    GLFL_LOAD_FUNCTION(MultiTexParameteriEXT);
    GLFL_LOAD_FUNCTION(MultiTexParameterivEXT);
    GLFL_LOAD_FUNCTION(MultiTexParameterfEXT);
    GLFL_LOAD_FUNCTION(MultiTexParameterfvEXT);
    GLFL_LOAD_FUNCTION(MultiTexImage1DEXT);
    GLFL_LOAD_FUNCTION(MultiTexImage2DEXT);
    GLFL_LOAD_FUNCTION(MultiTexSubImage1DEXT);
    GLFL_LOAD_FUNCTION(MultiTexSubImage2DEXT);
    GLFL_LOAD_FUNCTION(CopyMultiTexImage1DEXT);
    GLFL_LOAD_FUNCTION(CopyMultiTexImage2DEXT);
    GLFL_LOAD_FUNCTION(CopyMultiTexSubImage1DEXT);
    GLFL_LOAD_FUNCTION(CopyMultiTexSubImage2DEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexImageEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexParameterivEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexLevelParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexLevelParameterivEXT);
    GLFL_LOAD_FUNCTION(MultiTexImage3DEXT);
    GLFL_LOAD_FUNCTION(MultiTexSubImage3DEXT);
    GLFL_LOAD_FUNCTION(CopyMultiTexSubImage3DEXT);
    GLFL_LOAD_FUNCTION(EnableClientStateIndexedEXT);
    GLFL_LOAD_FUNCTION(DisableClientStateIndexedEXT);
    GLFL_LOAD_FUNCTION(GetFloatIndexedvEXT);
    GLFL_LOAD_FUNCTION(GetDoubleIndexedvEXT);
    GLFL_LOAD_FUNCTION(GetPointerIndexedvEXT);
    GLFL_LOAD_FUNCTION(EnableIndexedEXT);
    GLFL_LOAD_FUNCTION(DisableIndexedEXT);
    GLFL_LOAD_FUNCTION(IsEnabledIndexedEXT);
    GLFL_LOAD_FUNCTION(GetIntegerIndexedvEXT);
    GLFL_LOAD_FUNCTION(GetBooleanIndexedvEXT);
    GLFL_LOAD_FUNCTION(CompressedTextureImage3DEXT);
    GLFL_LOAD_FUNCTION(CompressedTextureImage2DEXT);
    GLFL_LOAD_FUNCTION(CompressedTextureImage1DEXT);
    GLFL_LOAD_FUNCTION(CompressedTextureSubImage3DEXT);
    GLFL_LOAD_FUNCTION(CompressedTextureSubImage2DEXT);
    GLFL_LOAD_FUNCTION(CompressedTextureSubImage1DEXT);
    GLFL_LOAD_FUNCTION(GetCompressedTextureImageEXT);
    GLFL_LOAD_FUNCTION(CompressedMultiTexImage3DEXT);
    GLFL_LOAD_FUNCTION(CompressedMultiTexImage2DEXT);
    GLFL_LOAD_FUNCTION(CompressedMultiTexImage1DEXT);
    GLFL_LOAD_FUNCTION(CompressedMultiTexSubImage3DEXT);
    GLFL_LOAD_FUNCTION(CompressedMultiTexSubImage2DEXT);
    GLFL_LOAD_FUNCTION(CompressedMultiTexSubImage1DEXT);
    GLFL_LOAD_FUNCTION(GetCompressedMultiTexImageEXT);
    GLFL_LOAD_FUNCTION(MatrixLoadTransposefEXT);
    GLFL_LOAD_FUNCTION(MatrixLoadTransposedEXT);
    GLFL_LOAD_FUNCTION(MatrixMultTransposefEXT);
    GLFL_LOAD_FUNCTION(MatrixMultTransposedEXT);
    GLFL_LOAD_FUNCTION(NamedBufferDataEXT);
    GLFL_LOAD_FUNCTION(NamedBufferSubDataEXT);
    GLFL_LOAD_FUNCTION(MapNamedBufferEXT);
    GLFL_LOAD_FUNCTION(UnmapNamedBufferEXT);
    GLFL_LOAD_FUNCTION(GetNamedBufferParameterivEXT);
    GLFL_LOAD_FUNCTION(GetNamedBufferPointervEXT);
    GLFL_LOAD_FUNCTION(GetNamedBufferSubDataEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3fvEXT);
    GLFL_LOAD_FUNCTION(TextureBufferEXT);
    GLFL_LOAD_FUNCTION(MultiTexBufferEXT);
    GLFL_LOAD_FUNCTION(TextureParameterIivEXT);
    GLFL_LOAD_FUNCTION(TextureParameterIuivEXT);
    GLFL_LOAD_FUNCTION(GetTextureParameterIivEXT);
    GLFL_LOAD_FUNCTION(GetTextureParameterIuivEXT);
    GLFL_LOAD_FUNCTION(MultiTexParameterIivEXT);
    GLFL_LOAD_FUNCTION(MultiTexParameterIuivEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexParameterIivEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexParameterIuivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4uivEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameters4fvEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameterI4iEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameterI4ivEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParametersI4ivEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameterI4uiEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameterI4uivEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParametersI4uivEXT);
    GLFL_LOAD_FUNCTION(GetNamedProgramLocalParameterIivEXT);
    GLFL_LOAD_FUNCTION(GetNamedProgramLocalParameterIuivEXT);
    GLFL_LOAD_FUNCTION(EnableClientStateiEXT);
    GLFL_LOAD_FUNCTION(DisableClientStateiEXT);
    GLFL_LOAD_FUNCTION(GetFloati_vEXT);
    GLFL_LOAD_FUNCTION(GetDoublei_vEXT);
    GLFL_LOAD_FUNCTION(GetPointeri_vEXT);
    GLFL_LOAD_FUNCTION(NamedProgramStringEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameter4dEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameter4dvEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameter4fEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameter4fvEXT);
    GLFL_LOAD_FUNCTION(GetNamedProgramLocalParameterdvEXT);
    GLFL_LOAD_FUNCTION(GetNamedProgramLocalParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetNamedProgramivEXT);
    GLFL_LOAD_FUNCTION(GetNamedProgramStringEXT);
    GLFL_LOAD_FUNCTION(NamedRenderbufferStorageEXT);
    GLFL_LOAD_FUNCTION(GetNamedRenderbufferParameterivEXT);
    GLFL_LOAD_FUNCTION(NamedRenderbufferStorageMultisampleEXT);
    GLFL_LOAD_FUNCTION(NamedRenderbufferStorageMultisampleCoverageEXT);
    GLFL_LOAD_FUNCTION(CheckNamedFramebufferStatusEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferTexture1DEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferTexture2DEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferTexture3DEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferRenderbufferEXT);
    GLFL_LOAD_FUNCTION(GetNamedFramebufferAttachmentParameterivEXT);
    GLFL_LOAD_FUNCTION(GenerateTextureMipmapEXT);
    GLFL_LOAD_FUNCTION(GenerateMultiTexMipmapEXT);
    GLFL_LOAD_FUNCTION(FramebufferDrawBufferEXT);
    GLFL_LOAD_FUNCTION(FramebufferDrawBuffersEXT);
    GLFL_LOAD_FUNCTION(FramebufferReadBufferEXT);
    GLFL_LOAD_FUNCTION(GetFramebufferParameterivEXT);
    GLFL_LOAD_FUNCTION(NamedCopyBufferSubDataEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferTextureEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferTextureLayerEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferTextureFaceEXT);
    GLFL_LOAD_FUNCTION(TextureRenderbufferEXT);
    GLFL_LOAD_FUNCTION(MultiTexRenderbufferEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayColorOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayEdgeFlagOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayIndexOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayNormalOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayTexCoordOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayMultiTexCoordOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayFogCoordOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArraySecondaryColorOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribIOffsetEXT);
    GLFL_LOAD_FUNCTION(EnableVertexArrayEXT);
    GLFL_LOAD_FUNCTION(DisableVertexArrayEXT);
    GLFL_LOAD_FUNCTION(EnableVertexArrayAttribEXT);
    GLFL_LOAD_FUNCTION(DisableVertexArrayAttribEXT);
    GLFL_LOAD_FUNCTION(GetVertexArrayIntegervEXT);
    GLFL_LOAD_FUNCTION(GetVertexArrayPointervEXT);
    GLFL_LOAD_FUNCTION(GetVertexArrayIntegeri_vEXT);
    GLFL_LOAD_FUNCTION(GetVertexArrayPointeri_vEXT);
    GLFL_LOAD_FUNCTION(MapNamedBufferRangeEXT);
    GLFL_LOAD_FUNCTION(FlushMappedNamedBufferRangeEXT);
    GLFL_LOAD_FUNCTION(NamedBufferStorageEXT);
    GLFL_LOAD_FUNCTION(ClearNamedBufferDataEXT);
    GLFL_LOAD_FUNCTION(ClearNamedBufferSubDataEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferParameteriEXT);
    GLFL_LOAD_FUNCTION(GetNamedFramebufferParameterivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1dEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2dEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3dEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4dEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3dvEXT);
    GLFL_LOAD_FUNCTION(TextureBufferRangeEXT);
    GLFL_LOAD_FUNCTION(TextureStorage1DEXT);
    GLFL_LOAD_FUNCTION(TextureStorage2DEXT);
    GLFL_LOAD_FUNCTION(TextureStorage3DEXT);
    GLFL_LOAD_FUNCTION(TextureStorage2DMultisampleEXT);
    GLFL_LOAD_FUNCTION(TextureStorage3DMultisampleEXT);
    GLFL_LOAD_FUNCTION(VertexArrayBindVertexBufferEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribFormatEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribIFormatEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribLFormatEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribBindingEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexBindingDivisorEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribLOffsetEXT);
    GLFL_LOAD_FUNCTION(TexturePageCommitmentEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribDivisorEXT);
}
void glfl::load_extension_GL_EXT_discard_framebuffer()
{
    GLFL_LOAD_FUNCTION(DiscardFramebufferEXT);
}
void glfl::load_extension_GL_EXT_disjoint_timer_query()
{
    GLFL_LOAD_FUNCTION(GenQueriesEXT);
    GLFL_LOAD_FUNCTION(DeleteQueriesEXT);
    GLFL_LOAD_FUNCTION(IsQueryEXT);
    GLFL_LOAD_FUNCTION(BeginQueryEXT);
    GLFL_LOAD_FUNCTION(EndQueryEXT);
    GLFL_LOAD_FUNCTION(QueryCounterEXT);
    GLFL_LOAD_FUNCTION(GetQueryivEXT);
    GLFL_LOAD_FUNCTION(GetQueryObjectivEXT);
    GLFL_LOAD_FUNCTION(GetQueryObjectuivEXT);
    GLFL_LOAD_FUNCTION(GetQueryObjecti64vEXT);
    GLFL_LOAD_FUNCTION(GetQueryObjectui64vEXT);
}
void glfl::load_extension_GL_EXT_draw_buffers()
{
    GLFL_LOAD_FUNCTION(DrawBuffersEXT);
}
void glfl::load_extension_GL_EXT_draw_buffers2()
{
    GLFL_LOAD_FUNCTION(ColorMaskIndexedEXT);
    GLFL_LOAD_FUNCTION(GetBooleanIndexedvEXT);
    GLFL_LOAD_FUNCTION(GetIntegerIndexedvEXT);
    GLFL_LOAD_FUNCTION(EnableIndexedEXT);
    GLFL_LOAD_FUNCTION(DisableIndexedEXT);
    GLFL_LOAD_FUNCTION(IsEnabledIndexedEXT);
}
void glfl::load_extension_GL_EXT_draw_buffers_indexed()
{
    GLFL_LOAD_FUNCTION(EnableiEXT);
    GLFL_LOAD_FUNCTION(DisableiEXT);
    GLFL_LOAD_FUNCTION(BlendEquationiEXT);
    GLFL_LOAD_FUNCTION(BlendEquationSeparateiEXT);
    GLFL_LOAD_FUNCTION(BlendFunciEXT);
    GLFL_LOAD_FUNCTION(BlendFuncSeparateiEXT);
    GLFL_LOAD_FUNCTION(ColorMaskiEXT);
    GLFL_LOAD_FUNCTION(IsEnablediEXT);
}
void glfl::load_extension_GL_EXT_draw_elements_base_vertex()
{
    GLFL_LOAD_FUNCTION(DrawElementsBaseVertexEXT);
    GLFL_LOAD_FUNCTION(DrawRangeElementsBaseVertexEXT);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertexEXT);
    GLFL_LOAD_FUNCTION(MultiDrawElementsBaseVertexEXT);
}
void glfl::load_extension_GL_EXT_draw_instanced()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedEXT);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedEXT);
}
void glfl::load_extension_GL_EXT_draw_range_elements()
{
    GLFL_LOAD_FUNCTION(DrawRangeElementsEXT);
}
void glfl::load_extension_GL_EXT_draw_transform_feedback()
{
    GLFL_LOAD_FUNCTION(DrawTransformFeedbackEXT);
    GLFL_LOAD_FUNCTION(DrawTransformFeedbackInstancedEXT);
}
void glfl::load_extension_GL_EXT_float_blend() {}
void glfl::load_extension_GL_EXT_fog_coord()
{
    GLFL_LOAD_FUNCTION(FogCoordfEXT);
    GLFL_LOAD_FUNCTION(FogCoordfvEXT);
    GLFL_LOAD_FUNCTION(FogCoorddEXT);
    GLFL_LOAD_FUNCTION(FogCoorddvEXT);
    GLFL_LOAD_FUNCTION(FogCoordPointerEXT);
}
void glfl::load_extension_GL_EXT_framebuffer_blit()
{
    GLFL_LOAD_FUNCTION(BlitFramebufferEXT);
}
void glfl::load_extension_GL_EXT_framebuffer_multisample()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleEXT);
}
void glfl::load_extension_GL_EXT_framebuffer_multisample_blit_scaled() {}
void glfl::load_extension_GL_EXT_framebuffer_object()
{
    GLFL_LOAD_FUNCTION(IsRenderbufferEXT);
    GLFL_LOAD_FUNCTION(BindRenderbufferEXT);
    GLFL_LOAD_FUNCTION(DeleteRenderbuffersEXT);
    GLFL_LOAD_FUNCTION(GenRenderbuffersEXT);
    GLFL_LOAD_FUNCTION(RenderbufferStorageEXT);
    GLFL_LOAD_FUNCTION(GetRenderbufferParameterivEXT);
    GLFL_LOAD_FUNCTION(IsFramebufferEXT);
    GLFL_LOAD_FUNCTION(BindFramebufferEXT);
    GLFL_LOAD_FUNCTION(DeleteFramebuffersEXT);
    GLFL_LOAD_FUNCTION(GenFramebuffersEXT);
    GLFL_LOAD_FUNCTION(CheckFramebufferStatusEXT);
    GLFL_LOAD_FUNCTION(FramebufferTexture1DEXT);
    GLFL_LOAD_FUNCTION(FramebufferTexture2DEXT);
    GLFL_LOAD_FUNCTION(FramebufferTexture3DEXT);
    GLFL_LOAD_FUNCTION(FramebufferRenderbufferEXT);
    GLFL_LOAD_FUNCTION(GetFramebufferAttachmentParameterivEXT);
    GLFL_LOAD_FUNCTION(GenerateMipmapEXT);
}
void glfl::load_extension_GL_EXT_framebuffer_sRGB() {}
void glfl::load_extension_GL_EXT_geometry_point_size() {}
void glfl::load_extension_GL_EXT_geometry_shader()
{
    GLFL_LOAD_FUNCTION(FramebufferTextureEXT);
}
void glfl::load_extension_GL_EXT_geometry_shader4()
{
    GLFL_LOAD_FUNCTION(ProgramParameteriEXT);
}
void glfl::load_extension_GL_EXT_gpu_program_parameters()
{
    GLFL_LOAD_FUNCTION(ProgramEnvParameters4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramLocalParameters4fvEXT);
}
void glfl::load_extension_GL_EXT_gpu_shader4()
{
    GLFL_LOAD_FUNCTION(GetUniformuivEXT);
    GLFL_LOAD_FUNCTION(BindFragDataLocationEXT);
    GLFL_LOAD_FUNCTION(GetFragDataLocationEXT);
    GLFL_LOAD_FUNCTION(Uniform1uiEXT);
    GLFL_LOAD_FUNCTION(Uniform2uiEXT);
    GLFL_LOAD_FUNCTION(Uniform3uiEXT);
    GLFL_LOAD_FUNCTION(Uniform4uiEXT);
    GLFL_LOAD_FUNCTION(Uniform1uivEXT);
    GLFL_LOAD_FUNCTION(Uniform2uivEXT);
    GLFL_LOAD_FUNCTION(Uniform3uivEXT);
    GLFL_LOAD_FUNCTION(Uniform4uivEXT);
}
void glfl::load_extension_GL_EXT_gpu_shader5() {}
void glfl::load_extension_GL_EXT_histogram()
{
    GLFL_LOAD_FUNCTION(GetHistogramEXT);
    GLFL_LOAD_FUNCTION(GetHistogramParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetHistogramParameterivEXT);
    GLFL_LOAD_FUNCTION(GetMinmaxEXT);
    GLFL_LOAD_FUNCTION(GetMinmaxParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetMinmaxParameterivEXT);
    GLFL_LOAD_FUNCTION(HistogramEXT);
    GLFL_LOAD_FUNCTION(MinmaxEXT);
    GLFL_LOAD_FUNCTION(ResetHistogramEXT);
    GLFL_LOAD_FUNCTION(ResetMinmaxEXT);
}
void glfl::load_extension_GL_EXT_index_array_formats() {}
void glfl::load_extension_GL_EXT_index_func()
{
    GLFL_LOAD_FUNCTION(IndexFuncEXT);
}
void glfl::load_extension_GL_EXT_index_material()
{
    GLFL_LOAD_FUNCTION(IndexMaterialEXT);
}
void glfl::load_extension_GL_EXT_index_texture() {}
void glfl::load_extension_GL_EXT_instanced_arrays()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedEXT);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedEXT);
    GLFL_LOAD_FUNCTION(VertexAttribDivisorEXT);
}
void glfl::load_extension_GL_EXT_light_texture()
{
    GLFL_LOAD_FUNCTION(ApplyTextureEXT);
    GLFL_LOAD_FUNCTION(TextureLightEXT);
    GLFL_LOAD_FUNCTION(TextureMaterialEXT);
}
void glfl::load_extension_GL_EXT_map_buffer_range()
{
    GLFL_LOAD_FUNCTION(MapBufferRangeEXT);
    GLFL_LOAD_FUNCTION(FlushMappedBufferRangeEXT);
}
void glfl::load_extension_GL_EXT_misc_attribute() {}
void glfl::load_extension_GL_EXT_multi_draw_arrays()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysEXT);
    GLFL_LOAD_FUNCTION(MultiDrawElementsEXT);
}
void glfl::load_extension_GL_EXT_multi_draw_indirect()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysIndirectEXT);
    GLFL_LOAD_FUNCTION(MultiDrawElementsIndirectEXT);
}
void glfl::load_extension_GL_EXT_multisample()
{
    GLFL_LOAD_FUNCTION(SampleMaskEXT);
    GLFL_LOAD_FUNCTION(SamplePatternEXT);
}
void glfl::load_extension_GL_EXT_multisampled_compatibility() {}
void glfl::load_extension_GL_EXT_multisampled_render_to_texture()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleEXT);
    GLFL_LOAD_FUNCTION(FramebufferTexture2DMultisampleEXT);
}
void glfl::load_extension_GL_EXT_multiview_draw_buffers()
{
    GLFL_LOAD_FUNCTION(ReadBufferIndexedEXT);
    GLFL_LOAD_FUNCTION(DrawBuffersIndexedEXT);
    GLFL_LOAD_FUNCTION(GetIntegeri_vEXT);
}
void glfl::load_extension_GL_EXT_occlusion_query_boolean()
{
    GLFL_LOAD_FUNCTION(GenQueriesEXT);
    GLFL_LOAD_FUNCTION(DeleteQueriesEXT);
    GLFL_LOAD_FUNCTION(IsQueryEXT);
    GLFL_LOAD_FUNCTION(BeginQueryEXT);
    GLFL_LOAD_FUNCTION(EndQueryEXT);
    GLFL_LOAD_FUNCTION(GetQueryivEXT);
    GLFL_LOAD_FUNCTION(GetQueryObjectuivEXT);
}
void glfl::load_extension_GL_EXT_packed_depth_stencil() {}
void glfl::load_extension_GL_EXT_packed_float() {}
void glfl::load_extension_GL_EXT_packed_pixels() {}
void glfl::load_extension_GL_EXT_paletted_texture()
{
    GLFL_LOAD_FUNCTION(ColorTableEXT);
    GLFL_LOAD_FUNCTION(GetColorTableEXT);
    GLFL_LOAD_FUNCTION(GetColorTableParameterivEXT);
    GLFL_LOAD_FUNCTION(GetColorTableParameterfvEXT);
}
void glfl::load_extension_GL_EXT_pixel_buffer_object() {}
void glfl::load_extension_GL_EXT_pixel_transform()
{
    GLFL_LOAD_FUNCTION(PixelTransformParameteriEXT);
    GLFL_LOAD_FUNCTION(PixelTransformParameterfEXT);
    GLFL_LOAD_FUNCTION(PixelTransformParameterivEXT);
    GLFL_LOAD_FUNCTION(PixelTransformParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetPixelTransformParameterivEXT);
    GLFL_LOAD_FUNCTION(GetPixelTransformParameterfvEXT);
}
void glfl::load_extension_GL_EXT_pixel_transform_color_table() {}
void glfl::load_extension_GL_EXT_point_parameters()
{
    GLFL_LOAD_FUNCTION(PointParameterfEXT);
    GLFL_LOAD_FUNCTION(PointParameterfvEXT);
}
void glfl::load_extension_GL_EXT_polygon_offset()
{
    GLFL_LOAD_FUNCTION(PolygonOffsetEXT);
}
void glfl::load_extension_GL_EXT_polygon_offset_clamp()
{
    GLFL_LOAD_FUNCTION(PolygonOffsetClampEXT);
}
void glfl::load_extension_GL_EXT_post_depth_coverage() {}
void glfl::load_extension_GL_EXT_primitive_bounding_box()
{
    GLFL_LOAD_FUNCTION(PrimitiveBoundingBoxEXT);
}
void glfl::load_extension_GL_EXT_protected_textures() {}
void glfl::load_extension_GL_EXT_provoking_vertex()
{
    GLFL_LOAD_FUNCTION(ProvokingVertexEXT);
}
void glfl::load_extension_GL_EXT_pvrtc_sRGB() {}
void glfl::load_extension_GL_EXT_raster_multisample()
{
    GLFL_LOAD_FUNCTION(RasterSamplesEXT);
}
void glfl::load_extension_GL_EXT_read_format_bgra() {}
void glfl::load_extension_GL_EXT_render_snorm() {}
void glfl::load_extension_GL_EXT_rescale_normal() {}
void glfl::load_extension_GL_EXT_robustness()
{
    GLFL_LOAD_FUNCTION(GetGraphicsResetStatusEXT);
    GLFL_LOAD_FUNCTION(ReadnPixelsEXT);
    GLFL_LOAD_FUNCTION(GetnUniformfvEXT);
    GLFL_LOAD_FUNCTION(GetnUniformivEXT);
}
void glfl::load_extension_GL_EXT_sRGB() {}
void glfl::load_extension_GL_EXT_sRGB_write_control() {}
void glfl::load_extension_GL_EXT_secondary_color()
{
    GLFL_LOAD_FUNCTION(SecondaryColor3bEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3bvEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3dEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3dvEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3fEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3fvEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3iEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3ivEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3sEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3svEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3ubEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3ubvEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3uiEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3uivEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3usEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3usvEXT);
    GLFL_LOAD_FUNCTION(SecondaryColorPointerEXT);
}
void glfl::load_extension_GL_EXT_separate_shader_objects()
{
    GLFL_LOAD_FUNCTION(UseShaderProgramEXT);
    GLFL_LOAD_FUNCTION(ActiveProgramEXT);
    GLFL_LOAD_FUNCTION(CreateShaderProgramEXT);
    GLFL_LOAD_FUNCTION(ActiveShaderProgramEXT);
    GLFL_LOAD_FUNCTION(BindProgramPipelineEXT);
    GLFL_LOAD_FUNCTION(CreateShaderProgramvEXT);
    GLFL_LOAD_FUNCTION(DeleteProgramPipelinesEXT);
    GLFL_LOAD_FUNCTION(GenProgramPipelinesEXT);
    GLFL_LOAD_FUNCTION(GetProgramPipelineInfoLogEXT);
    GLFL_LOAD_FUNCTION(GetProgramPipelineivEXT);
    GLFL_LOAD_FUNCTION(IsProgramPipelineEXT);
    GLFL_LOAD_FUNCTION(ProgramParameteriEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4fvEXT);
    GLFL_LOAD_FUNCTION(UseProgramStagesEXT);
    GLFL_LOAD_FUNCTION(ValidateProgramPipelineEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3fvEXT);
}
void glfl::load_extension_GL_EXT_separate_specular_color() {}
void glfl::load_extension_GL_EXT_shader_framebuffer_fetch() {}
void glfl::load_extension_GL_EXT_shader_group_vote() {}
void glfl::load_extension_GL_EXT_shader_image_load_formatted() {}
void glfl::load_extension_GL_EXT_shader_image_load_store()
{
    GLFL_LOAD_FUNCTION(BindImageTextureEXT);
    GLFL_LOAD_FUNCTION(MemoryBarrierEXT);
}
void glfl::load_extension_GL_EXT_shader_implicit_conversions() {}
void glfl::load_extension_GL_EXT_shader_integer_mix() {}
void glfl::load_extension_GL_EXT_shader_io_blocks() {}
void glfl::load_extension_GL_EXT_shader_non_constant_global_initializers() {}
void glfl::load_extension_GL_EXT_shader_pixel_local_storage() {}
void glfl::load_extension_GL_EXT_shader_pixel_local_storage2()
{
    GLFL_LOAD_FUNCTION(FramebufferPixelLocalStorageSizeEXT);
    GLFL_LOAD_FUNCTION(GetFramebufferPixelLocalStorageSizeEXT);
    GLFL_LOAD_FUNCTION(ClearPixelLocalStorageuiEXT);
}
void glfl::load_extension_GL_EXT_shader_texture_lod() {}
void glfl::load_extension_GL_EXT_shadow_funcs() {}
void glfl::load_extension_GL_EXT_shadow_samplers() {}
void glfl::load_extension_GL_EXT_shared_texture_palette() {}
void glfl::load_extension_GL_EXT_sparse_texture()
{
    GLFL_LOAD_FUNCTION(TexPageCommitmentEXT);
}
void glfl::load_extension_GL_EXT_sparse_texture2() {}
void glfl::load_extension_GL_EXT_stencil_clear_tag()
{
    GLFL_LOAD_FUNCTION(StencilClearTagEXT);
}
void glfl::load_extension_GL_EXT_stencil_two_side()
{
    GLFL_LOAD_FUNCTION(ActiveStencilFaceEXT);
}
void glfl::load_extension_GL_EXT_stencil_wrap() {}
void glfl::load_extension_GL_EXT_subtexture()
{
    GLFL_LOAD_FUNCTION(TexSubImage1DEXT);
    GLFL_LOAD_FUNCTION(TexSubImage2DEXT);
}
void glfl::load_extension_GL_EXT_tessellation_point_size() {}
void glfl::load_extension_GL_EXT_tessellation_shader()
{
    GLFL_LOAD_FUNCTION(PatchParameteriEXT);
}
void glfl::load_extension_GL_EXT_texture() {}
void glfl::load_extension_GL_EXT_texture3D()
{
    GLFL_LOAD_FUNCTION(TexImage3DEXT);
    GLFL_LOAD_FUNCTION(TexSubImage3DEXT);
}
void glfl::load_extension_GL_EXT_texture_array()
{
    GLFL_LOAD_FUNCTION(FramebufferTextureLayerEXT);
}
void glfl::load_extension_GL_EXT_texture_border_clamp()
{
    GLFL_LOAD_FUNCTION(TexParameterIivEXT);
    GLFL_LOAD_FUNCTION(TexParameterIuivEXT);
    GLFL_LOAD_FUNCTION(GetTexParameterIivEXT);
    GLFL_LOAD_FUNCTION(GetTexParameterIuivEXT);
    GLFL_LOAD_FUNCTION(SamplerParameterIivEXT);
    GLFL_LOAD_FUNCTION(SamplerParameterIuivEXT);
    GLFL_LOAD_FUNCTION(GetSamplerParameterIivEXT);
    GLFL_LOAD_FUNCTION(GetSamplerParameterIuivEXT);
}
void glfl::load_extension_GL_EXT_texture_buffer()
{
    GLFL_LOAD_FUNCTION(TexBufferEXT);
    GLFL_LOAD_FUNCTION(TexBufferRangeEXT);
}
void glfl::load_extension_GL_EXT_texture_buffer_object()
{
    GLFL_LOAD_FUNCTION(TexBufferEXT);
}
void glfl::load_extension_GL_EXT_texture_compression_dxt1() {}
void glfl::load_extension_GL_EXT_texture_compression_latc() {}
void glfl::load_extension_GL_EXT_texture_compression_rgtc() {}
void glfl::load_extension_GL_EXT_texture_compression_s3tc() {}
void glfl::load_extension_GL_EXT_texture_cube_map() {}
void glfl::load_extension_GL_EXT_texture_cube_map_array() {}
void glfl::load_extension_GL_EXT_texture_env_add() {}
void glfl::load_extension_GL_EXT_texture_env_combine() {}
void glfl::load_extension_GL_EXT_texture_env_dot3() {}
void glfl::load_extension_GL_EXT_texture_filter_anisotropic() {}
void glfl::load_extension_GL_EXT_texture_filter_minmax()
{
    GLFL_LOAD_FUNCTION(RasterSamplesEXT);
}
void glfl::load_extension_GL_EXT_texture_format_BGRA8888() {}
void glfl::load_extension_GL_EXT_texture_integer()
{
    GLFL_LOAD_FUNCTION(TexParameterIivEXT);
    GLFL_LOAD_FUNCTION(TexParameterIuivEXT);
    GLFL_LOAD_FUNCTION(GetTexParameterIivEXT);
    GLFL_LOAD_FUNCTION(GetTexParameterIuivEXT);
    GLFL_LOAD_FUNCTION(ClearColorIiEXT);
    GLFL_LOAD_FUNCTION(ClearColorIuiEXT);
}
void glfl::load_extension_GL_EXT_texture_lod_bias() {}
void glfl::load_extension_GL_EXT_texture_mirror_clamp() {}
void glfl::load_extension_GL_EXT_texture_norm16() {}
void glfl::load_extension_GL_EXT_texture_object()
{
    GLFL_LOAD_FUNCTION(AreTexturesResidentEXT);
    GLFL_LOAD_FUNCTION(BindTextureEXT);
    GLFL_LOAD_FUNCTION(DeleteTexturesEXT);
    GLFL_LOAD_FUNCTION(GenTexturesEXT);
    GLFL_LOAD_FUNCTION(IsTextureEXT);
    GLFL_LOAD_FUNCTION(PrioritizeTexturesEXT);
}
void glfl::load_extension_GL_EXT_texture_perturb_normal()
{
    GLFL_LOAD_FUNCTION(TextureNormalEXT);
}
void glfl::load_extension_GL_EXT_texture_rg() {}
void glfl::load_extension_GL_EXT_texture_sRGB() {}
void glfl::load_extension_GL_EXT_texture_sRGB_R8() {}
void glfl::load_extension_GL_EXT_texture_sRGB_RG8() {}
void glfl::load_extension_GL_EXT_texture_sRGB_decode() {}
void glfl::load_extension_GL_EXT_texture_shared_exponent() {}
void glfl::load_extension_GL_EXT_texture_snorm() {}
void glfl::load_extension_GL_EXT_texture_storage()
{
    GLFL_LOAD_FUNCTION(TexStorage1DEXT);
    GLFL_LOAD_FUNCTION(TexStorage2DEXT);
    GLFL_LOAD_FUNCTION(TexStorage3DEXT);
    GLFL_LOAD_FUNCTION(TextureStorage1DEXT);
    GLFL_LOAD_FUNCTION(TextureStorage2DEXT);
    GLFL_LOAD_FUNCTION(TextureStorage3DEXT);
}
void glfl::load_extension_GL_EXT_texture_swizzle() {}
void glfl::load_extension_GL_EXT_texture_type_2_10_10_10_REV() {}
void glfl::load_extension_GL_EXT_texture_view()
{
    GLFL_LOAD_FUNCTION(TextureViewEXT);
}
void glfl::load_extension_GL_EXT_timer_query()
{
    GLFL_LOAD_FUNCTION(GetQueryObjecti64vEXT);
    GLFL_LOAD_FUNCTION(GetQueryObjectui64vEXT);
}
void glfl::load_extension_GL_EXT_transform_feedback()
{
    GLFL_LOAD_FUNCTION(BeginTransformFeedbackEXT);
    GLFL_LOAD_FUNCTION(EndTransformFeedbackEXT);
    GLFL_LOAD_FUNCTION(BindBufferRangeEXT);
    GLFL_LOAD_FUNCTION(BindBufferOffsetEXT);
    GLFL_LOAD_FUNCTION(BindBufferBaseEXT);
    GLFL_LOAD_FUNCTION(TransformFeedbackVaryingsEXT);
    GLFL_LOAD_FUNCTION(GetTransformFeedbackVaryingEXT);
}
void glfl::load_extension_GL_EXT_unpack_subimage() {}
void glfl::load_extension_GL_EXT_vertex_array()
{
    GLFL_LOAD_FUNCTION(ArrayElementEXT);
    GLFL_LOAD_FUNCTION(ColorPointerEXT);
    GLFL_LOAD_FUNCTION(DrawArraysEXT);
    GLFL_LOAD_FUNCTION(EdgeFlagPointerEXT);
    GLFL_LOAD_FUNCTION(GetPointervEXT);
    GLFL_LOAD_FUNCTION(IndexPointerEXT);
    GLFL_LOAD_FUNCTION(NormalPointerEXT);
    GLFL_LOAD_FUNCTION(TexCoordPointerEXT);
    GLFL_LOAD_FUNCTION(VertexPointerEXT);
}
void glfl::load_extension_GL_EXT_vertex_array_bgra() {}
void glfl::load_extension_GL_EXT_vertex_attrib_64bit()
{
    GLFL_LOAD_FUNCTION(VertexAttribL1dEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL2dEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL3dEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL4dEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL1dvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL2dvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL3dvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL4dvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribLPointerEXT);
    GLFL_LOAD_FUNCTION(GetVertexAttribLdvEXT);
}
void glfl::load_extension_GL_EXT_vertex_shader()
{
    GLFL_LOAD_FUNCTION(BeginVertexShaderEXT);
    GLFL_LOAD_FUNCTION(EndVertexShaderEXT);
    GLFL_LOAD_FUNCTION(BindVertexShaderEXT);
    GLFL_LOAD_FUNCTION(GenVertexShadersEXT);
    GLFL_LOAD_FUNCTION(DeleteVertexShaderEXT);
    GLFL_LOAD_FUNCTION(ShaderOp1EXT);
    GLFL_LOAD_FUNCTION(ShaderOp2EXT);
    GLFL_LOAD_FUNCTION(ShaderOp3EXT);
    GLFL_LOAD_FUNCTION(SwizzleEXT);
    GLFL_LOAD_FUNCTION(WriteMaskEXT);
    GLFL_LOAD_FUNCTION(InsertComponentEXT);
    GLFL_LOAD_FUNCTION(ExtractComponentEXT);
    GLFL_LOAD_FUNCTION(GenSymbolsEXT);
    GLFL_LOAD_FUNCTION(SetInvariantEXT);
    GLFL_LOAD_FUNCTION(SetLocalConstantEXT);
    GLFL_LOAD_FUNCTION(VariantbvEXT);
    GLFL_LOAD_FUNCTION(VariantsvEXT);
    GLFL_LOAD_FUNCTION(VariantivEXT);
    GLFL_LOAD_FUNCTION(VariantfvEXT);
    GLFL_LOAD_FUNCTION(VariantdvEXT);
    GLFL_LOAD_FUNCTION(VariantubvEXT);
    GLFL_LOAD_FUNCTION(VariantusvEXT);
    GLFL_LOAD_FUNCTION(VariantuivEXT);
    GLFL_LOAD_FUNCTION(VariantPointerEXT);
    GLFL_LOAD_FUNCTION(EnableVariantClientStateEXT);
    GLFL_LOAD_FUNCTION(DisableVariantClientStateEXT);
    GLFL_LOAD_FUNCTION(BindLightParameterEXT);
    GLFL_LOAD_FUNCTION(BindMaterialParameterEXT);
    GLFL_LOAD_FUNCTION(BindTexGenParameterEXT);
    GLFL_LOAD_FUNCTION(BindTextureUnitParameterEXT);
    GLFL_LOAD_FUNCTION(BindParameterEXT);
    GLFL_LOAD_FUNCTION(IsVariantEnabledEXT);
    GLFL_LOAD_FUNCTION(GetVariantBooleanvEXT);
    GLFL_LOAD_FUNCTION(GetVariantIntegervEXT);
    GLFL_LOAD_FUNCTION(GetVariantFloatvEXT);
    GLFL_LOAD_FUNCTION(GetVariantPointervEXT);
    GLFL_LOAD_FUNCTION(GetInvariantBooleanvEXT);
    GLFL_LOAD_FUNCTION(GetInvariantIntegervEXT);
    GLFL_LOAD_FUNCTION(GetInvariantFloatvEXT);
    GLFL_LOAD_FUNCTION(GetLocalConstantBooleanvEXT);
    GLFL_LOAD_FUNCTION(GetLocalConstantIntegervEXT);
    GLFL_LOAD_FUNCTION(GetLocalConstantFloatvEXT);
}
void glfl::load_extension_GL_EXT_vertex_weighting()
{
    GLFL_LOAD_FUNCTION(VertexWeightfEXT);
    GLFL_LOAD_FUNCTION(VertexWeightfvEXT);
    GLFL_LOAD_FUNCTION(VertexWeightPointerEXT);
}
void glfl::load_extension_GL_EXT_window_rectangles()
{
    GLFL_LOAD_FUNCTION(WindowRectanglesEXT);
}
void glfl::load_extension_GL_EXT_x11_sync_object()
{
    GLFL_LOAD_FUNCTION(ImportSyncEXT);
}
void glfl::load_extension_GL_FJ_shader_binary_GCCSO() {}
void glfl::load_extension_GL_GREMEDY_frame_terminator()
{
    GLFL_LOAD_FUNCTION(FrameTerminatorGREMEDY);
}
void glfl::load_extension_GL_GREMEDY_string_marker()
{
    GLFL_LOAD_FUNCTION(StringMarkerGREMEDY);
}
void glfl::load_extension_GL_HP_convolution_border_modes() {}
void glfl::load_extension_GL_HP_image_transform()
{
    GLFL_LOAD_FUNCTION(ImageTransformParameteriHP);
    GLFL_LOAD_FUNCTION(ImageTransformParameterfHP);
    GLFL_LOAD_FUNCTION(ImageTransformParameterivHP);
    GLFL_LOAD_FUNCTION(ImageTransformParameterfvHP);
    GLFL_LOAD_FUNCTION(GetImageTransformParameterivHP);
    GLFL_LOAD_FUNCTION(GetImageTransformParameterfvHP);
}
void glfl::load_extension_GL_HP_occlusion_test() {}
void glfl::load_extension_GL_HP_texture_lighting() {}
void glfl::load_extension_GL_IBM_cull_vertex() {}
void glfl::load_extension_GL_IBM_multimode_draw_arrays()
{
    GLFL_LOAD_FUNCTION(MultiModeDrawArraysIBM);
    GLFL_LOAD_FUNCTION(MultiModeDrawElementsIBM);
}
void glfl::load_extension_GL_IBM_rasterpos_clip() {}
void glfl::load_extension_GL_IBM_static_data()
{
    GLFL_LOAD_FUNCTION(FlushStaticDataIBM);
}
void glfl::load_extension_GL_IBM_texture_mirrored_repeat() {}
void glfl::load_extension_GL_IBM_vertex_array_lists()
{
    GLFL_LOAD_FUNCTION(ColorPointerListIBM);
    GLFL_LOAD_FUNCTION(SecondaryColorPointerListIBM);
    GLFL_LOAD_FUNCTION(EdgeFlagPointerListIBM);
    GLFL_LOAD_FUNCTION(FogCoordPointerListIBM);
    GLFL_LOAD_FUNCTION(IndexPointerListIBM);
    GLFL_LOAD_FUNCTION(NormalPointerListIBM);
    GLFL_LOAD_FUNCTION(TexCoordPointerListIBM);
    GLFL_LOAD_FUNCTION(VertexPointerListIBM);
}
void glfl::load_extension_GL_IMG_bindless_texture()
{
    GLFL_LOAD_FUNCTION(GetTextureHandleIMG);
    GLFL_LOAD_FUNCTION(GetTextureSamplerHandleIMG);
    GLFL_LOAD_FUNCTION(UniformHandleui64IMG);
    GLFL_LOAD_FUNCTION(UniformHandleui64vIMG);
    GLFL_LOAD_FUNCTION(ProgramUniformHandleui64IMG);
    GLFL_LOAD_FUNCTION(ProgramUniformHandleui64vIMG);
}
void glfl::load_extension_GL_IMG_framebuffer_downsample()
{
    GLFL_LOAD_FUNCTION(FramebufferTexture2DDownsampleIMG);
    GLFL_LOAD_FUNCTION(FramebufferTextureLayerDownsampleIMG);
}
void glfl::load_extension_GL_IMG_multisampled_render_to_texture()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleIMG);
    GLFL_LOAD_FUNCTION(FramebufferTexture2DMultisampleIMG);
}
void glfl::load_extension_GL_IMG_program_binary() {}
void glfl::load_extension_GL_IMG_read_format() {}
void glfl::load_extension_GL_IMG_shader_binary() {}
void glfl::load_extension_GL_IMG_texture_compression_pvrtc() {}
void glfl::load_extension_GL_IMG_texture_compression_pvrtc2() {}
void glfl::load_extension_GL_IMG_texture_env_enhanced_fixed_function() {}
void glfl::load_extension_GL_IMG_texture_filter_cubic() {}
void glfl::load_extension_GL_IMG_user_clip_plane()
{
    GLFL_LOAD_FUNCTION(ClipPlanefIMG);
    GLFL_LOAD_FUNCTION(ClipPlanexIMG);
}
void glfl::load_extension_GL_INGR_blend_func_separate()
{
    GLFL_LOAD_FUNCTION(BlendFuncSeparateINGR);
}
void glfl::load_extension_GL_INGR_color_clamp() {}
void glfl::load_extension_GL_INGR_interlace_read() {}
void glfl::load_extension_GL_INTEL_conservative_rasterization() {}
void glfl::load_extension_GL_INTEL_fragment_shader_ordering() {}
void glfl::load_extension_GL_INTEL_framebuffer_CMAA()
{
    GLFL_LOAD_FUNCTION(ApplyFramebufferAttachmentCMAAINTEL);
}
void glfl::load_extension_GL_INTEL_map_texture()
{
    GLFL_LOAD_FUNCTION(SyncTextureINTEL);
    GLFL_LOAD_FUNCTION(UnmapTexture2DINTEL);
    GLFL_LOAD_FUNCTION(MapTexture2DINTEL);
}
void glfl::load_extension_GL_INTEL_parallel_arrays()
{
    GLFL_LOAD_FUNCTION(VertexPointervINTEL);
    GLFL_LOAD_FUNCTION(NormalPointervINTEL);
    GLFL_LOAD_FUNCTION(ColorPointervINTEL);
    GLFL_LOAD_FUNCTION(TexCoordPointervINTEL);
}
void glfl::load_extension_GL_INTEL_performance_query()
{
    GLFL_LOAD_FUNCTION(BeginPerfQueryINTEL);
    GLFL_LOAD_FUNCTION(CreatePerfQueryINTEL);
    GLFL_LOAD_FUNCTION(DeletePerfQueryINTEL);
    GLFL_LOAD_FUNCTION(EndPerfQueryINTEL);
    GLFL_LOAD_FUNCTION(GetFirstPerfQueryIdINTEL);
    GLFL_LOAD_FUNCTION(GetNextPerfQueryIdINTEL);
    GLFL_LOAD_FUNCTION(GetPerfCounterInfoINTEL);
    GLFL_LOAD_FUNCTION(GetPerfQueryDataINTEL);
    GLFL_LOAD_FUNCTION(GetPerfQueryIdByNameINTEL);
    GLFL_LOAD_FUNCTION(GetPerfQueryInfoINTEL);
}
void glfl::load_extension_GL_KHR_blend_equation_advanced()
{
    GLFL_LOAD_FUNCTION(BlendBarrierKHR);
}
void glfl::load_extension_GL_KHR_blend_equation_advanced_coherent() {}
void glfl::load_extension_GL_KHR_context_flush_control() {}
void glfl::load_extension_GL_KHR_debug()
{
    GLFL_LOAD_FUNCTION(DebugMessageControl);
    GLFL_LOAD_FUNCTION(DebugMessageInsert);
    GLFL_LOAD_FUNCTION(DebugMessageCallback);
    GLFL_LOAD_FUNCTION(GetDebugMessageLog);
    GLFL_LOAD_FUNCTION(PushDebugGroup);
    GLFL_LOAD_FUNCTION(PopDebugGroup);
    GLFL_LOAD_FUNCTION(ObjectLabel);
    GLFL_LOAD_FUNCTION(GetObjectLabel);
    GLFL_LOAD_FUNCTION(ObjectPtrLabel);
    GLFL_LOAD_FUNCTION(GetObjectPtrLabel);
    GLFL_LOAD_FUNCTION(GetPointerv);
    GLFL_LOAD_FUNCTION(DebugMessageControlKHR);
    GLFL_LOAD_FUNCTION(DebugMessageInsertKHR);
    GLFL_LOAD_FUNCTION(DebugMessageCallbackKHR);
    GLFL_LOAD_FUNCTION(GetDebugMessageLogKHR);
    GLFL_LOAD_FUNCTION(PushDebugGroupKHR);
    GLFL_LOAD_FUNCTION(PopDebugGroupKHR);
    GLFL_LOAD_FUNCTION(ObjectLabelKHR);
    GLFL_LOAD_FUNCTION(GetObjectLabelKHR);
    GLFL_LOAD_FUNCTION(ObjectPtrLabelKHR);
    GLFL_LOAD_FUNCTION(GetObjectPtrLabelKHR);
    GLFL_LOAD_FUNCTION(GetPointervKHR);
}
void glfl::load_extension_GL_KHR_no_error() {}
void glfl::load_extension_GL_KHR_robust_buffer_access_behavior() {}
void glfl::load_extension_GL_KHR_robustness()
{
    GLFL_LOAD_FUNCTION(GetGraphicsResetStatus);
    GLFL_LOAD_FUNCTION(ReadnPixels);
    GLFL_LOAD_FUNCTION(GetnUniformfv);
    GLFL_LOAD_FUNCTION(GetnUniformiv);
    GLFL_LOAD_FUNCTION(GetnUniformuiv);
    GLFL_LOAD_FUNCTION(GetGraphicsResetStatusKHR);
    GLFL_LOAD_FUNCTION(ReadnPixelsKHR);
    GLFL_LOAD_FUNCTION(GetnUniformfvKHR);
    GLFL_LOAD_FUNCTION(GetnUniformivKHR);
    GLFL_LOAD_FUNCTION(GetnUniformuivKHR);
}
void glfl::load_extension_GL_KHR_texture_compression_astc_hdr() {}
void glfl::load_extension_GL_KHR_texture_compression_astc_ldr() {}
void glfl::load_extension_GL_KHR_texture_compression_astc_sliced_3d() {}
void glfl::load_extension_GL_MESAX_texture_stack() {}
void glfl::load_extension_GL_MESA_pack_invert() {}
void glfl::load_extension_GL_MESA_resize_buffers()
{
    GLFL_LOAD_FUNCTION(ResizeBuffersMESA);
}
void glfl::load_extension_GL_MESA_window_pos()
{
    GLFL_LOAD_FUNCTION(WindowPos2dMESA);
    GLFL_LOAD_FUNCTION(WindowPos2dvMESA);
    GLFL_LOAD_FUNCTION(WindowPos2fMESA);
    GLFL_LOAD_FUNCTION(WindowPos2fvMESA);
    GLFL_LOAD_FUNCTION(WindowPos2iMESA);
    GLFL_LOAD_FUNCTION(WindowPos2ivMESA);
    GLFL_LOAD_FUNCTION(WindowPos2sMESA);
    GLFL_LOAD_FUNCTION(WindowPos2svMESA);
    GLFL_LOAD_FUNCTION(WindowPos3dMESA);
    GLFL_LOAD_FUNCTION(WindowPos3dvMESA);
    GLFL_LOAD_FUNCTION(WindowPos3fMESA);
    GLFL_LOAD_FUNCTION(WindowPos3fvMESA);
    GLFL_LOAD_FUNCTION(WindowPos3iMESA);
    GLFL_LOAD_FUNCTION(WindowPos3ivMESA);
    GLFL_LOAD_FUNCTION(WindowPos3sMESA);
    GLFL_LOAD_FUNCTION(WindowPos3svMESA);
    GLFL_LOAD_FUNCTION(WindowPos4dMESA);
    GLFL_LOAD_FUNCTION(WindowPos4dvMESA);
    GLFL_LOAD_FUNCTION(WindowPos4fMESA);
    GLFL_LOAD_FUNCTION(WindowPos4fvMESA);
    GLFL_LOAD_FUNCTION(WindowPos4iMESA);
    GLFL_LOAD_FUNCTION(WindowPos4ivMESA);
    GLFL_LOAD_FUNCTION(WindowPos4sMESA);
    GLFL_LOAD_FUNCTION(WindowPos4svMESA);
}
void glfl::load_extension_GL_MESA_ycbcr_texture() {}
void glfl::load_extension_GL_NVX_conditional_render()
{
    GLFL_LOAD_FUNCTION(BeginConditionalRenderNVX);
    GLFL_LOAD_FUNCTION(EndConditionalRenderNVX);
}
void glfl::load_extension_GL_NVX_gpu_memory_info() {}
void glfl::load_extension_GL_NV_bindless_multi_draw_indirect()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysIndirectBindlessNV);
    GLFL_LOAD_FUNCTION(MultiDrawElementsIndirectBindlessNV);
}
void glfl::load_extension_GL_NV_bindless_multi_draw_indirect_count()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysIndirectBindlessCountNV);
    GLFL_LOAD_FUNCTION(MultiDrawElementsIndirectBindlessCountNV);
}
void glfl::load_extension_GL_NV_bindless_texture()
{
    GLFL_LOAD_FUNCTION(GetTextureHandleNV);
    GLFL_LOAD_FUNCTION(GetTextureSamplerHandleNV);
    GLFL_LOAD_FUNCTION(MakeTextureHandleResidentNV);
    GLFL_LOAD_FUNCTION(MakeTextureHandleNonResidentNV);
    GLFL_LOAD_FUNCTION(GetImageHandleNV);
    GLFL_LOAD_FUNCTION(MakeImageHandleResidentNV);
    GLFL_LOAD_FUNCTION(MakeImageHandleNonResidentNV);
    GLFL_LOAD_FUNCTION(UniformHandleui64NV);
    GLFL_LOAD_FUNCTION(UniformHandleui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniformHandleui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniformHandleui64vNV);
    GLFL_LOAD_FUNCTION(IsTextureHandleResidentNV);
    GLFL_LOAD_FUNCTION(IsImageHandleResidentNV);
}
void glfl::load_extension_GL_NV_blend_equation_advanced()
{
    GLFL_LOAD_FUNCTION(BlendParameteriNV);
    GLFL_LOAD_FUNCTION(BlendBarrierNV);
}
void glfl::load_extension_GL_NV_blend_equation_advanced_coherent() {}
void glfl::load_extension_GL_NV_blend_square() {}
void glfl::load_extension_GL_NV_clip_space_w_scaling()
{
    GLFL_LOAD_FUNCTION(ViewportPositionWScaleNV);
}
void glfl::load_extension_GL_NV_command_list()
{
    GLFL_LOAD_FUNCTION(CreateStatesNV);
    GLFL_LOAD_FUNCTION(DeleteStatesNV);
    GLFL_LOAD_FUNCTION(IsStateNV);
    GLFL_LOAD_FUNCTION(StateCaptureNV);
    GLFL_LOAD_FUNCTION(GetCommandHeaderNV);
    GLFL_LOAD_FUNCTION(GetStageIndexNV);
    GLFL_LOAD_FUNCTION(DrawCommandsNV);
    GLFL_LOAD_FUNCTION(DrawCommandsAddressNV);
    GLFL_LOAD_FUNCTION(DrawCommandsStatesNV);
    GLFL_LOAD_FUNCTION(DrawCommandsStatesAddressNV);
    GLFL_LOAD_FUNCTION(CreateCommandListsNV);
    GLFL_LOAD_FUNCTION(DeleteCommandListsNV);
    GLFL_LOAD_FUNCTION(IsCommandListNV);
    GLFL_LOAD_FUNCTION(ListDrawCommandsStatesClientNV);
    GLFL_LOAD_FUNCTION(CommandListSegmentsNV);
    GLFL_LOAD_FUNCTION(CompileCommandListNV);
    GLFL_LOAD_FUNCTION(CallCommandListNV);
}
void glfl::load_extension_GL_NV_compute_program5() {}
void glfl::load_extension_GL_NV_conditional_render()
{
    GLFL_LOAD_FUNCTION(BeginConditionalRenderNV);
    GLFL_LOAD_FUNCTION(EndConditionalRenderNV);
}
void glfl::load_extension_GL_NV_conservative_raster()
{
    GLFL_LOAD_FUNCTION(SubpixelPrecisionBiasNV);
}
void glfl::load_extension_GL_NV_conservative_raster_dilate()
{
    GLFL_LOAD_FUNCTION(ConservativeRasterParameterfNV);
}
void glfl::load_extension_GL_NV_conservative_raster_pre_snap_triangles()
{
    GLFL_LOAD_FUNCTION(ConservativeRasterParameteriNV);
}
void glfl::load_extension_GL_NV_copy_buffer()
{
    GLFL_LOAD_FUNCTION(CopyBufferSubDataNV);
}
void glfl::load_extension_GL_NV_copy_depth_to_color() {}
void glfl::load_extension_GL_NV_copy_image()
{
    GLFL_LOAD_FUNCTION(CopyImageSubDataNV);
}
void glfl::load_extension_GL_NV_coverage_sample()
{
    GLFL_LOAD_FUNCTION(CoverageMaskNV);
    GLFL_LOAD_FUNCTION(CoverageOperationNV);
}
void glfl::load_extension_GL_NV_deep_texture3D() {}
void glfl::load_extension_GL_NV_depth_buffer_float()
{
    GLFL_LOAD_FUNCTION(DepthRangedNV);
    GLFL_LOAD_FUNCTION(ClearDepthdNV);
    GLFL_LOAD_FUNCTION(DepthBoundsdNV);
}
void glfl::load_extension_GL_NV_depth_clamp() {}
void glfl::load_extension_GL_NV_depth_nonlinear() {}
void glfl::load_extension_GL_NV_draw_buffers()
{
    GLFL_LOAD_FUNCTION(DrawBuffersNV);
}
void glfl::load_extension_GL_NV_draw_instanced()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedNV);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedNV);
}
void glfl::load_extension_GL_NV_draw_texture()
{
    GLFL_LOAD_FUNCTION(DrawTextureNV);
}
void glfl::load_extension_GL_NV_evaluators()
{
    GLFL_LOAD_FUNCTION(MapControlPointsNV);
    GLFL_LOAD_FUNCTION(MapParameterivNV);
    GLFL_LOAD_FUNCTION(MapParameterfvNV);
    GLFL_LOAD_FUNCTION(GetMapControlPointsNV);
    GLFL_LOAD_FUNCTION(GetMapParameterivNV);
    GLFL_LOAD_FUNCTION(GetMapParameterfvNV);
    GLFL_LOAD_FUNCTION(GetMapAttribParameterivNV);
    GLFL_LOAD_FUNCTION(GetMapAttribParameterfvNV);
    GLFL_LOAD_FUNCTION(EvalMapsNV);
}
void glfl::load_extension_GL_NV_explicit_attrib_location() {}
void glfl::load_extension_GL_NV_explicit_multisample()
{
    GLFL_LOAD_FUNCTION(GetMultisamplefvNV);
    GLFL_LOAD_FUNCTION(SampleMaskIndexedNV);
    GLFL_LOAD_FUNCTION(TexRenderbufferNV);
}
void glfl::load_extension_GL_NV_fbo_color_attachments() {}
void glfl::load_extension_GL_NV_fence()
{
    GLFL_LOAD_FUNCTION(DeleteFencesNV);
    GLFL_LOAD_FUNCTION(GenFencesNV);
    GLFL_LOAD_FUNCTION(IsFenceNV);
    GLFL_LOAD_FUNCTION(TestFenceNV);
    GLFL_LOAD_FUNCTION(GetFenceivNV);
    GLFL_LOAD_FUNCTION(FinishFenceNV);
    GLFL_LOAD_FUNCTION(SetFenceNV);
}
void glfl::load_extension_GL_NV_fill_rectangle() {}
void glfl::load_extension_GL_NV_float_buffer() {}
void glfl::load_extension_GL_NV_fog_distance() {}
void glfl::load_extension_GL_NV_fragment_coverage_to_color()
{
    GLFL_LOAD_FUNCTION(FragmentCoverageColorNV);
}
void glfl::load_extension_GL_NV_fragment_program()
{
    GLFL_LOAD_FUNCTION(ProgramNamedParameter4fNV);
    GLFL_LOAD_FUNCTION(ProgramNamedParameter4fvNV);
    GLFL_LOAD_FUNCTION(ProgramNamedParameter4dNV);
    GLFL_LOAD_FUNCTION(ProgramNamedParameter4dvNV);
    GLFL_LOAD_FUNCTION(GetProgramNamedParameterfvNV);
    GLFL_LOAD_FUNCTION(GetProgramNamedParameterdvNV);
}
void glfl::load_extension_GL_NV_fragment_program2() {}
void glfl::load_extension_GL_NV_fragment_program4() {}
void glfl::load_extension_GL_NV_fragment_program_option() {}
void glfl::load_extension_GL_NV_fragment_shader_interlock() {}
void glfl::load_extension_GL_NV_framebuffer_blit()
{
    GLFL_LOAD_FUNCTION(BlitFramebufferNV);
}
void glfl::load_extension_GL_NV_framebuffer_mixed_samples()
{
    GLFL_LOAD_FUNCTION(RasterSamplesEXT);
    GLFL_LOAD_FUNCTION(CoverageModulationTableNV);
    GLFL_LOAD_FUNCTION(GetCoverageModulationTableNV);
    GLFL_LOAD_FUNCTION(CoverageModulationNV);
}
void glfl::load_extension_GL_NV_framebuffer_multisample()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleNV);
}
void glfl::load_extension_GL_NV_framebuffer_multisample_coverage()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleCoverageNV);
}
void glfl::load_extension_GL_NV_generate_mipmap_sRGB() {}
void glfl::load_extension_GL_NV_geometry_program4()
{
    GLFL_LOAD_FUNCTION(ProgramVertexLimitNV);
    GLFL_LOAD_FUNCTION(FramebufferTextureEXT);
    GLFL_LOAD_FUNCTION(FramebufferTextureLayerEXT);
    GLFL_LOAD_FUNCTION(FramebufferTextureFaceEXT);
}
void glfl::load_extension_GL_NV_geometry_shader4() {}
void glfl::load_extension_GL_NV_geometry_shader_passthrough() {}
void glfl::load_extension_GL_NV_gpu_program4()
{
    GLFL_LOAD_FUNCTION(ProgramLocalParameterI4iNV);
    GLFL_LOAD_FUNCTION(ProgramLocalParameterI4ivNV);
    GLFL_LOAD_FUNCTION(ProgramLocalParametersI4ivNV);
    GLFL_LOAD_FUNCTION(ProgramLocalParameterI4uiNV);
    GLFL_LOAD_FUNCTION(ProgramLocalParameterI4uivNV);
    GLFL_LOAD_FUNCTION(ProgramLocalParametersI4uivNV);
    GLFL_LOAD_FUNCTION(ProgramEnvParameterI4iNV);
    GLFL_LOAD_FUNCTION(ProgramEnvParameterI4ivNV);
    GLFL_LOAD_FUNCTION(ProgramEnvParametersI4ivNV);
    GLFL_LOAD_FUNCTION(ProgramEnvParameterI4uiNV);
    GLFL_LOAD_FUNCTION(ProgramEnvParameterI4uivNV);
    GLFL_LOAD_FUNCTION(ProgramEnvParametersI4uivNV);
    GLFL_LOAD_FUNCTION(GetProgramLocalParameterIivNV);
    GLFL_LOAD_FUNCTION(GetProgramLocalParameterIuivNV);
    GLFL_LOAD_FUNCTION(GetProgramEnvParameterIivNV);
    GLFL_LOAD_FUNCTION(GetProgramEnvParameterIuivNV);
}
void glfl::load_extension_GL_NV_gpu_program5()
{
    GLFL_LOAD_FUNCTION(ProgramSubroutineParametersuivNV);
    GLFL_LOAD_FUNCTION(GetProgramSubroutineParameteruivNV);
}
void glfl::load_extension_GL_NV_gpu_program5_mem_extended() {}
void glfl::load_extension_GL_NV_gpu_shader5()
{
    GLFL_LOAD_FUNCTION(Uniform1i64NV);
    GLFL_LOAD_FUNCTION(Uniform2i64NV);
    GLFL_LOAD_FUNCTION(Uniform3i64NV);
    GLFL_LOAD_FUNCTION(Uniform4i64NV);
    GLFL_LOAD_FUNCTION(Uniform1i64vNV);
    GLFL_LOAD_FUNCTION(Uniform2i64vNV);
    GLFL_LOAD_FUNCTION(Uniform3i64vNV);
    GLFL_LOAD_FUNCTION(Uniform4i64vNV);
    GLFL_LOAD_FUNCTION(Uniform1ui64NV);
    GLFL_LOAD_FUNCTION(Uniform2ui64NV);
    GLFL_LOAD_FUNCTION(Uniform3ui64NV);
    GLFL_LOAD_FUNCTION(Uniform4ui64NV);
    GLFL_LOAD_FUNCTION(Uniform1ui64vNV);
    GLFL_LOAD_FUNCTION(Uniform2ui64vNV);
    GLFL_LOAD_FUNCTION(Uniform3ui64vNV);
    GLFL_LOAD_FUNCTION(Uniform4ui64vNV);
    GLFL_LOAD_FUNCTION(GetUniformi64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform1i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform2i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform3i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform4i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform1i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform2i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform3i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform4i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui64vNV);
}
void glfl::load_extension_GL_NV_half_float()
{
    GLFL_LOAD_FUNCTION(Vertex2hNV);
    GLFL_LOAD_FUNCTION(Vertex2hvNV);
    GLFL_LOAD_FUNCTION(Vertex3hNV);
    GLFL_LOAD_FUNCTION(Vertex3hvNV);
    GLFL_LOAD_FUNCTION(Vertex4hNV);
    GLFL_LOAD_FUNCTION(Vertex4hvNV);
    GLFL_LOAD_FUNCTION(Normal3hNV);
    GLFL_LOAD_FUNCTION(Normal3hvNV);
    GLFL_LOAD_FUNCTION(Color3hNV);
    GLFL_LOAD_FUNCTION(Color3hvNV);
    GLFL_LOAD_FUNCTION(Color4hNV);
    GLFL_LOAD_FUNCTION(Color4hvNV);
    GLFL_LOAD_FUNCTION(TexCoord1hNV);
    GLFL_LOAD_FUNCTION(TexCoord1hvNV);
    GLFL_LOAD_FUNCTION(TexCoord2hNV);
    GLFL_LOAD_FUNCTION(TexCoord2hvNV);
    GLFL_LOAD_FUNCTION(TexCoord3hNV);
    GLFL_LOAD_FUNCTION(TexCoord3hvNV);
    GLFL_LOAD_FUNCTION(TexCoord4hNV);
    GLFL_LOAD_FUNCTION(TexCoord4hvNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord1hNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord1hvNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord2hNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord2hvNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord3hNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord3hvNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord4hNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord4hvNV);
    GLFL_LOAD_FUNCTION(FogCoordhNV);
    GLFL_LOAD_FUNCTION(FogCoordhvNV);
    GLFL_LOAD_FUNCTION(SecondaryColor3hNV);
    GLFL_LOAD_FUNCTION(SecondaryColor3hvNV);
    GLFL_LOAD_FUNCTION(VertexWeighthNV);
    GLFL_LOAD_FUNCTION(VertexWeighthvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1hNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1hvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2hNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2hvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3hNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3hvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4hNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4hvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs1hvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs2hvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs3hvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs4hvNV);
}
void glfl::load_extension_GL_NV_image_formats() {}
void glfl::load_extension_GL_NV_instanced_arrays()
{
    GLFL_LOAD_FUNCTION(VertexAttribDivisorNV);
}
void glfl::load_extension_GL_NV_internalformat_sample_query()
{
    GLFL_LOAD_FUNCTION(GetInternalformatSampleivNV);
}
void glfl::load_extension_GL_NV_light_max_exponent() {}
void glfl::load_extension_GL_NV_multisample_coverage() {}
void glfl::load_extension_GL_NV_multisample_filter_hint() {}
void glfl::load_extension_GL_NV_non_square_matrices()
{
    GLFL_LOAD_FUNCTION(UniformMatrix2x3fvNV);
    GLFL_LOAD_FUNCTION(UniformMatrix3x2fvNV);
    GLFL_LOAD_FUNCTION(UniformMatrix2x4fvNV);
    GLFL_LOAD_FUNCTION(UniformMatrix4x2fvNV);
    GLFL_LOAD_FUNCTION(UniformMatrix3x4fvNV);
    GLFL_LOAD_FUNCTION(UniformMatrix4x3fvNV);
}
void glfl::load_extension_GL_NV_occlusion_query()
{
    GLFL_LOAD_FUNCTION(GenOcclusionQueriesNV);
    GLFL_LOAD_FUNCTION(DeleteOcclusionQueriesNV);
    GLFL_LOAD_FUNCTION(IsOcclusionQueryNV);
    GLFL_LOAD_FUNCTION(BeginOcclusionQueryNV);
    GLFL_LOAD_FUNCTION(EndOcclusionQueryNV);
    GLFL_LOAD_FUNCTION(GetOcclusionQueryivNV);
    GLFL_LOAD_FUNCTION(GetOcclusionQueryuivNV);
}
void glfl::load_extension_GL_NV_packed_depth_stencil() {}
void glfl::load_extension_GL_NV_parameter_buffer_object()
{
    GLFL_LOAD_FUNCTION(ProgramBufferParametersfvNV);
    GLFL_LOAD_FUNCTION(ProgramBufferParametersIivNV);
    GLFL_LOAD_FUNCTION(ProgramBufferParametersIuivNV);
}
void glfl::load_extension_GL_NV_parameter_buffer_object2() {}
void glfl::load_extension_GL_NV_path_rendering()
{
    GLFL_LOAD_FUNCTION(GenPathsNV);
    GLFL_LOAD_FUNCTION(DeletePathsNV);
    GLFL_LOAD_FUNCTION(IsPathNV);
    GLFL_LOAD_FUNCTION(PathCommandsNV);
    GLFL_LOAD_FUNCTION(PathCoordsNV);
    GLFL_LOAD_FUNCTION(PathSubCommandsNV);
    GLFL_LOAD_FUNCTION(PathSubCoordsNV);
    GLFL_LOAD_FUNCTION(PathStringNV);
    GLFL_LOAD_FUNCTION(PathGlyphsNV);
    GLFL_LOAD_FUNCTION(PathGlyphRangeNV);
    GLFL_LOAD_FUNCTION(WeightPathsNV);
    GLFL_LOAD_FUNCTION(CopyPathNV);
    GLFL_LOAD_FUNCTION(InterpolatePathsNV);
    GLFL_LOAD_FUNCTION(TransformPathNV);
    GLFL_LOAD_FUNCTION(PathParameterivNV);
    GLFL_LOAD_FUNCTION(PathParameteriNV);
    GLFL_LOAD_FUNCTION(PathParameterfvNV);
    GLFL_LOAD_FUNCTION(PathParameterfNV);
    GLFL_LOAD_FUNCTION(PathDashArrayNV);
    GLFL_LOAD_FUNCTION(PathStencilFuncNV);
    GLFL_LOAD_FUNCTION(PathStencilDepthOffsetNV);
    GLFL_LOAD_FUNCTION(StencilFillPathNV);
    GLFL_LOAD_FUNCTION(StencilStrokePathNV);
    GLFL_LOAD_FUNCTION(StencilFillPathInstancedNV);
    GLFL_LOAD_FUNCTION(StencilStrokePathInstancedNV);
    GLFL_LOAD_FUNCTION(PathCoverDepthFuncNV);
    GLFL_LOAD_FUNCTION(CoverFillPathNV);
    GLFL_LOAD_FUNCTION(CoverStrokePathNV);
    GLFL_LOAD_FUNCTION(CoverFillPathInstancedNV);
    GLFL_LOAD_FUNCTION(CoverStrokePathInstancedNV);
    GLFL_LOAD_FUNCTION(GetPathParameterivNV);
    GLFL_LOAD_FUNCTION(GetPathParameterfvNV);
    GLFL_LOAD_FUNCTION(GetPathCommandsNV);
    GLFL_LOAD_FUNCTION(GetPathCoordsNV);
    GLFL_LOAD_FUNCTION(GetPathDashArrayNV);
    GLFL_LOAD_FUNCTION(GetPathMetricsNV);
    GLFL_LOAD_FUNCTION(GetPathMetricRangeNV);
    GLFL_LOAD_FUNCTION(GetPathSpacingNV);
    GLFL_LOAD_FUNCTION(IsPointInFillPathNV);
    GLFL_LOAD_FUNCTION(IsPointInStrokePathNV);
    GLFL_LOAD_FUNCTION(GetPathLengthNV);
    GLFL_LOAD_FUNCTION(PointAlongPathNV);
    GLFL_LOAD_FUNCTION(MatrixLoad3x2fNV);
    GLFL_LOAD_FUNCTION(MatrixLoad3x3fNV);
    GLFL_LOAD_FUNCTION(MatrixLoadTranspose3x3fNV);
    GLFL_LOAD_FUNCTION(MatrixMult3x2fNV);
    GLFL_LOAD_FUNCTION(MatrixMult3x3fNV);
    GLFL_LOAD_FUNCTION(MatrixMultTranspose3x3fNV);
    GLFL_LOAD_FUNCTION(StencilThenCoverFillPathNV);
    GLFL_LOAD_FUNCTION(StencilThenCoverStrokePathNV);
    GLFL_LOAD_FUNCTION(StencilThenCoverFillPathInstancedNV);
    GLFL_LOAD_FUNCTION(StencilThenCoverStrokePathInstancedNV);
    GLFL_LOAD_FUNCTION(PathGlyphIndexRangeNV);
    GLFL_LOAD_FUNCTION(PathGlyphIndexArrayNV);
    GLFL_LOAD_FUNCTION(PathMemoryGlyphIndexArrayNV);
    GLFL_LOAD_FUNCTION(ProgramPathFragmentInputGenNV);
    GLFL_LOAD_FUNCTION(GetProgramResourcefvNV);
    GLFL_LOAD_FUNCTION(PathColorGenNV);
    GLFL_LOAD_FUNCTION(PathTexGenNV);
    GLFL_LOAD_FUNCTION(PathFogGenNV);
    GLFL_LOAD_FUNCTION(GetPathColorGenivNV);
    GLFL_LOAD_FUNCTION(GetPathColorGenfvNV);
    GLFL_LOAD_FUNCTION(GetPathTexGenivNV);
    GLFL_LOAD_FUNCTION(GetPathTexGenfvNV);
}
void glfl::load_extension_GL_NV_path_rendering_shared_edge() {}
void glfl::load_extension_GL_NV_pixel_data_range()
{
    GLFL_LOAD_FUNCTION(PixelDataRangeNV);
    GLFL_LOAD_FUNCTION(FlushPixelDataRangeNV);
}
void glfl::load_extension_GL_NV_point_sprite()
{
    GLFL_LOAD_FUNCTION(PointParameteriNV);
    GLFL_LOAD_FUNCTION(PointParameterivNV);
}
void glfl::load_extension_GL_NV_polygon_mode()
{
    GLFL_LOAD_FUNCTION(PolygonModeNV);
}
void glfl::load_extension_GL_NV_present_video()
{
    GLFL_LOAD_FUNCTION(PresentFrameKeyedNV);
    GLFL_LOAD_FUNCTION(PresentFrameDualFillNV);
    GLFL_LOAD_FUNCTION(GetVideoivNV);
    GLFL_LOAD_FUNCTION(GetVideouivNV);
    GLFL_LOAD_FUNCTION(GetVideoi64vNV);
    GLFL_LOAD_FUNCTION(GetVideoui64vNV);
}
void glfl::load_extension_GL_NV_primitive_restart()
{
    GLFL_LOAD_FUNCTION(PrimitiveRestartNV);
    GLFL_LOAD_FUNCTION(PrimitiveRestartIndexNV);
}
void glfl::load_extension_GL_NV_read_buffer()
{
    GLFL_LOAD_FUNCTION(ReadBufferNV);
}
void glfl::load_extension_GL_NV_read_buffer_front() {}
void glfl::load_extension_GL_NV_read_depth() {}
void glfl::load_extension_GL_NV_read_depth_stencil() {}
void glfl::load_extension_GL_NV_read_stencil() {}
void glfl::load_extension_GL_NV_register_combiners()
{
    GLFL_LOAD_FUNCTION(CombinerParameterfvNV);
    GLFL_LOAD_FUNCTION(CombinerParameterfNV);
    GLFL_LOAD_FUNCTION(CombinerParameterivNV);
    GLFL_LOAD_FUNCTION(CombinerParameteriNV);
    GLFL_LOAD_FUNCTION(CombinerInputNV);
    GLFL_LOAD_FUNCTION(CombinerOutputNV);
    GLFL_LOAD_FUNCTION(FinalCombinerInputNV);
    GLFL_LOAD_FUNCTION(GetCombinerInputParameterfvNV);
    GLFL_LOAD_FUNCTION(GetCombinerInputParameterivNV);
    GLFL_LOAD_FUNCTION(GetCombinerOutputParameterfvNV);
    GLFL_LOAD_FUNCTION(GetCombinerOutputParameterivNV);
    GLFL_LOAD_FUNCTION(GetFinalCombinerInputParameterfvNV);
    GLFL_LOAD_FUNCTION(GetFinalCombinerInputParameterivNV);
}
void glfl::load_extension_GL_NV_register_combiners2()
{
    GLFL_LOAD_FUNCTION(CombinerStageParameterfvNV);
    GLFL_LOAD_FUNCTION(GetCombinerStageParameterfvNV);
}
void glfl::load_extension_GL_NV_robustness_video_memory_purge() {}
void glfl::load_extension_GL_NV_sRGB_formats() {}
void glfl::load_extension_GL_NV_sample_locations()
{
    GLFL_LOAD_FUNCTION(FramebufferSampleLocationsfvNV);
    GLFL_LOAD_FUNCTION(NamedFramebufferSampleLocationsfvNV);
    GLFL_LOAD_FUNCTION(ResolveDepthValuesNV);
}
void glfl::load_extension_GL_NV_sample_mask_override_coverage() {}
void glfl::load_extension_GL_NV_shader_atomic_counters() {}
void glfl::load_extension_GL_NV_shader_atomic_float() {}
void glfl::load_extension_GL_NV_shader_atomic_float64() {}
void glfl::load_extension_GL_NV_shader_atomic_fp16_vector() {}
void glfl::load_extension_GL_NV_shader_atomic_int64() {}
void glfl::load_extension_GL_NV_shader_buffer_load()
{
    GLFL_LOAD_FUNCTION(MakeBufferResidentNV);
    GLFL_LOAD_FUNCTION(MakeBufferNonResidentNV);
    GLFL_LOAD_FUNCTION(IsBufferResidentNV);
    GLFL_LOAD_FUNCTION(MakeNamedBufferResidentNV);
    GLFL_LOAD_FUNCTION(MakeNamedBufferNonResidentNV);
    GLFL_LOAD_FUNCTION(IsNamedBufferResidentNV);
    GLFL_LOAD_FUNCTION(GetBufferParameterui64vNV);
    GLFL_LOAD_FUNCTION(GetNamedBufferParameterui64vNV);
    GLFL_LOAD_FUNCTION(GetIntegerui64vNV);
    GLFL_LOAD_FUNCTION(Uniformui64NV);
    GLFL_LOAD_FUNCTION(Uniformui64vNV);
    GLFL_LOAD_FUNCTION(GetUniformui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniformui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniformui64vNV);
}
void glfl::load_extension_GL_NV_shader_buffer_store() {}
void glfl::load_extension_GL_NV_shader_noperspective_interpolation() {}
void glfl::load_extension_GL_NV_shader_storage_buffer_object() {}
void glfl::load_extension_GL_NV_shader_thread_group() {}
void glfl::load_extension_GL_NV_shader_thread_shuffle() {}
void glfl::load_extension_GL_NV_shadow_samplers_array() {}
void glfl::load_extension_GL_NV_shadow_samplers_cube() {}
void glfl::load_extension_GL_NV_stereo_view_rendering() {}
void glfl::load_extension_GL_NV_tessellation_program5() {}
void glfl::load_extension_GL_NV_texgen_emboss() {}
void glfl::load_extension_GL_NV_texgen_reflection() {}
void glfl::load_extension_GL_NV_texture_barrier()
{
    GLFL_LOAD_FUNCTION(TextureBarrierNV);
}
void glfl::load_extension_GL_NV_texture_border_clamp() {}
void glfl::load_extension_GL_NV_texture_compression_s3tc_update() {}
void glfl::load_extension_GL_NV_texture_compression_vtc() {}
void glfl::load_extension_GL_NV_texture_env_combine4() {}
void glfl::load_extension_GL_NV_texture_expand_normal() {}
void glfl::load_extension_GL_NV_texture_multisample()
{
    GLFL_LOAD_FUNCTION(TexImage2DMultisampleCoverageNV);
    GLFL_LOAD_FUNCTION(TexImage3DMultisampleCoverageNV);
    GLFL_LOAD_FUNCTION(TextureImage2DMultisampleNV);
    GLFL_LOAD_FUNCTION(TextureImage3DMultisampleNV);
    GLFL_LOAD_FUNCTION(TextureImage2DMultisampleCoverageNV);
    GLFL_LOAD_FUNCTION(TextureImage3DMultisampleCoverageNV);
}
void glfl::load_extension_GL_NV_texture_npot_2D_mipmap() {}
void glfl::load_extension_GL_NV_texture_rectangle() {}
void glfl::load_extension_GL_NV_texture_shader() {}
void glfl::load_extension_GL_NV_texture_shader2() {}
void glfl::load_extension_GL_NV_texture_shader3() {}
void glfl::load_extension_GL_NV_transform_feedback()
{
    GLFL_LOAD_FUNCTION(BeginTransformFeedbackNV);
    GLFL_LOAD_FUNCTION(EndTransformFeedbackNV);
    GLFL_LOAD_FUNCTION(TransformFeedbackAttribsNV);
    GLFL_LOAD_FUNCTION(BindBufferRangeNV);
    GLFL_LOAD_FUNCTION(BindBufferOffsetNV);
    GLFL_LOAD_FUNCTION(BindBufferBaseNV);
    GLFL_LOAD_FUNCTION(TransformFeedbackVaryingsNV);
    GLFL_LOAD_FUNCTION(ActiveVaryingNV);
    GLFL_LOAD_FUNCTION(GetVaryingLocationNV);
    GLFL_LOAD_FUNCTION(GetActiveVaryingNV);
    GLFL_LOAD_FUNCTION(GetTransformFeedbackVaryingNV);
    GLFL_LOAD_FUNCTION(TransformFeedbackStreamAttribsNV);
}
void glfl::load_extension_GL_NV_transform_feedback2()
{
    GLFL_LOAD_FUNCTION(BindTransformFeedbackNV);
    GLFL_LOAD_FUNCTION(DeleteTransformFeedbacksNV);
    GLFL_LOAD_FUNCTION(GenTransformFeedbacksNV);
    GLFL_LOAD_FUNCTION(IsTransformFeedbackNV);
    GLFL_LOAD_FUNCTION(PauseTransformFeedbackNV);
    GLFL_LOAD_FUNCTION(ResumeTransformFeedbackNV);
    GLFL_LOAD_FUNCTION(DrawTransformFeedbackNV);
}
void glfl::load_extension_GL_NV_uniform_buffer_unified_memory() {}
void glfl::load_extension_GL_NV_vdpau_interop()
{
    GLFL_LOAD_FUNCTION(VDPAUInitNV);
    GLFL_LOAD_FUNCTION(VDPAUFiniNV);
    GLFL_LOAD_FUNCTION(VDPAURegisterVideoSurfaceNV);
    GLFL_LOAD_FUNCTION(VDPAURegisterOutputSurfaceNV);
    GLFL_LOAD_FUNCTION(VDPAUIsSurfaceNV);
    GLFL_LOAD_FUNCTION(VDPAUUnregisterSurfaceNV);
    GLFL_LOAD_FUNCTION(VDPAUGetSurfaceivNV);
    GLFL_LOAD_FUNCTION(VDPAUSurfaceAccessNV);
    GLFL_LOAD_FUNCTION(VDPAUMapSurfacesNV);
    GLFL_LOAD_FUNCTION(VDPAUUnmapSurfacesNV);
}
void glfl::load_extension_GL_NV_vertex_array_range()
{
    GLFL_LOAD_FUNCTION(FlushVertexArrayRangeNV);
    GLFL_LOAD_FUNCTION(VertexArrayRangeNV);
}
void glfl::load_extension_GL_NV_vertex_array_range2() {}
void glfl::load_extension_GL_NV_vertex_attrib_integer_64bit()
{
    GLFL_LOAD_FUNCTION(VertexAttribL1i64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL2i64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL3i64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL4i64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL1i64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL2i64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL3i64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL4i64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL1ui64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL2ui64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL3ui64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL4ui64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL1ui64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL2ui64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL3ui64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL4ui64vNV);
    GLFL_LOAD_FUNCTION(GetVertexAttribLi64vNV);
    GLFL_LOAD_FUNCTION(GetVertexAttribLui64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribLFormatNV);
}
void glfl::load_extension_GL_NV_vertex_buffer_unified_memory()
{
    GLFL_LOAD_FUNCTION(BufferAddressRangeNV);
    GLFL_LOAD_FUNCTION(VertexFormatNV);
    GLFL_LOAD_FUNCTION(NormalFormatNV);
    GLFL_LOAD_FUNCTION(ColorFormatNV);
    GLFL_LOAD_FUNCTION(IndexFormatNV);
    GLFL_LOAD_FUNCTION(TexCoordFormatNV);
    GLFL_LOAD_FUNCTION(EdgeFlagFormatNV);
    GLFL_LOAD_FUNCTION(SecondaryColorFormatNV);
    GLFL_LOAD_FUNCTION(FogCoordFormatNV);
    GLFL_LOAD_FUNCTION(VertexAttribFormatNV);
    GLFL_LOAD_FUNCTION(VertexAttribIFormatNV);
    GLFL_LOAD_FUNCTION(GetIntegerui64i_vNV);
}
void glfl::load_extension_GL_NV_vertex_program()
{
    GLFL_LOAD_FUNCTION(AreProgramsResidentNV);
    GLFL_LOAD_FUNCTION(BindProgramNV);
    GLFL_LOAD_FUNCTION(DeleteProgramsNV);
    GLFL_LOAD_FUNCTION(ExecuteProgramNV);
    GLFL_LOAD_FUNCTION(GenProgramsNV);
    GLFL_LOAD_FUNCTION(GetProgramParameterdvNV);
    GLFL_LOAD_FUNCTION(GetProgramParameterfvNV);
    GLFL_LOAD_FUNCTION(GetProgramivNV);
    GLFL_LOAD_FUNCTION(GetProgramStringNV);
    GLFL_LOAD_FUNCTION(GetTrackMatrixivNV);
    GLFL_LOAD_FUNCTION(GetVertexAttribdvNV);
    GLFL_LOAD_FUNCTION(GetVertexAttribfvNV);
    GLFL_LOAD_FUNCTION(GetVertexAttribivNV);
    GLFL_LOAD_FUNCTION(GetVertexAttribPointervNV);
    GLFL_LOAD_FUNCTION(IsProgramNV);
    GLFL_LOAD_FUNCTION(LoadProgramNV);
    GLFL_LOAD_FUNCTION(ProgramParameter4dNV);
    GLFL_LOAD_FUNCTION(ProgramParameter4dvNV);
    GLFL_LOAD_FUNCTION(ProgramParameter4fNV);
    GLFL_LOAD_FUNCTION(ProgramParameter4fvNV);
    GLFL_LOAD_FUNCTION(ProgramParameters4dvNV);
    GLFL_LOAD_FUNCTION(ProgramParameters4fvNV);
    GLFL_LOAD_FUNCTION(RequestResidentProgramsNV);
    GLFL_LOAD_FUNCTION(TrackMatrixNV);
    GLFL_LOAD_FUNCTION(VertexAttribPointerNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1dNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1dvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1fNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1fvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1sNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1svNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2dNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2dvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2fNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2fvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2sNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2svNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3dNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3dvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3fNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3fvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3sNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3svNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4dNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4dvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4fNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4fvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4sNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4svNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4ubNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4ubvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs1dvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs1fvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs1svNV);
    GLFL_LOAD_FUNCTION(VertexAttribs2dvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs2fvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs2svNV);
    GLFL_LOAD_FUNCTION(VertexAttribs3dvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs3fvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs3svNV);
    GLFL_LOAD_FUNCTION(VertexAttribs4dvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs4fvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs4svNV);
    GLFL_LOAD_FUNCTION(VertexAttribs4ubvNV);
}
void glfl::load_extension_GL_NV_vertex_program1_1() {}
void glfl::load_extension_GL_NV_vertex_program2() {}
void glfl::load_extension_GL_NV_vertex_program2_option() {}
void glfl::load_extension_GL_NV_vertex_program3() {}
void glfl::load_extension_GL_NV_vertex_program4()
{
    GLFL_LOAD_FUNCTION(VertexAttribI1iEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI2iEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI3iEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4iEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI1uiEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI2uiEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI3uiEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4uiEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI1ivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI2ivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI3ivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4ivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI1uivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI2uivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI3uivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4uivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4bvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4svEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4ubvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4usvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribIPointerEXT);
    GLFL_LOAD_FUNCTION(GetVertexAttribIivEXT);
    GLFL_LOAD_FUNCTION(GetVertexAttribIuivEXT);
}
void glfl::load_extension_GL_NV_video_capture()
{
    GLFL_LOAD_FUNCTION(BeginVideoCaptureNV);
    GLFL_LOAD_FUNCTION(BindVideoCaptureStreamBufferNV);
    GLFL_LOAD_FUNCTION(BindVideoCaptureStreamTextureNV);
    GLFL_LOAD_FUNCTION(EndVideoCaptureNV);
    GLFL_LOAD_FUNCTION(GetVideoCaptureivNV);
    GLFL_LOAD_FUNCTION(GetVideoCaptureStreamivNV);
    GLFL_LOAD_FUNCTION(GetVideoCaptureStreamfvNV);
    GLFL_LOAD_FUNCTION(GetVideoCaptureStreamdvNV);
    GLFL_LOAD_FUNCTION(VideoCaptureNV);
    GLFL_LOAD_FUNCTION(VideoCaptureStreamParameterivNV);
    GLFL_LOAD_FUNCTION(VideoCaptureStreamParameterfvNV);
    GLFL_LOAD_FUNCTION(VideoCaptureStreamParameterdvNV);
}
void glfl::load_extension_GL_NV_viewport_array()
{
    GLFL_LOAD_FUNCTION(ViewportArrayvNV);
    GLFL_LOAD_FUNCTION(ViewportIndexedfNV);
    GLFL_LOAD_FUNCTION(ViewportIndexedfvNV);
    GLFL_LOAD_FUNCTION(ScissorArrayvNV);
    GLFL_LOAD_FUNCTION(ScissorIndexedNV);
    GLFL_LOAD_FUNCTION(ScissorIndexedvNV);
    GLFL_LOAD_FUNCTION(DepthRangeArrayfvNV);
    GLFL_LOAD_FUNCTION(DepthRangeIndexedfNV);
    GLFL_LOAD_FUNCTION(GetFloati_vNV);
    GLFL_LOAD_FUNCTION(EnableiNV);
    GLFL_LOAD_FUNCTION(DisableiNV);
    GLFL_LOAD_FUNCTION(IsEnablediNV);
}
void glfl::load_extension_GL_NV_viewport_array2() {}
void glfl::load_extension_GL_NV_viewport_swizzle()
{
    GLFL_LOAD_FUNCTION(ViewportSwizzleNV);
}
void glfl::load_extension_GL_OES_EGL_image()
{
    GLFL_LOAD_FUNCTION(EGLImageTargetTexture2DOES);
    GLFL_LOAD_FUNCTION(EGLImageTargetRenderbufferStorageOES);
}
void glfl::load_extension_GL_OES_EGL_image_external() {}
void glfl::load_extension_GL_OES_EGL_image_external_essl3() {}
void glfl::load_extension_GL_OES_blend_equation_separate()
{
    GLFL_LOAD_FUNCTION(BlendEquationSeparateOES);
}
void glfl::load_extension_GL_OES_blend_func_separate()
{
    GLFL_LOAD_FUNCTION(BlendFuncSeparateOES);
}
void glfl::load_extension_GL_OES_blend_subtract()
{
    GLFL_LOAD_FUNCTION(BlendEquationOES);
}
void glfl::load_extension_GL_OES_byte_coordinates()
{
    GLFL_LOAD_FUNCTION(MultiTexCoord1bOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord1bvOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord2bOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord2bvOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord3bOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord3bvOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord4bOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord4bvOES);
    GLFL_LOAD_FUNCTION(TexCoord1bOES);
    GLFL_LOAD_FUNCTION(TexCoord1bvOES);
    GLFL_LOAD_FUNCTION(TexCoord2bOES);
    GLFL_LOAD_FUNCTION(TexCoord2bvOES);
    GLFL_LOAD_FUNCTION(TexCoord3bOES);
    GLFL_LOAD_FUNCTION(TexCoord3bvOES);
    GLFL_LOAD_FUNCTION(TexCoord4bOES);
    GLFL_LOAD_FUNCTION(TexCoord4bvOES);
    GLFL_LOAD_FUNCTION(Vertex2bOES);
    GLFL_LOAD_FUNCTION(Vertex2bvOES);
    GLFL_LOAD_FUNCTION(Vertex3bOES);
    GLFL_LOAD_FUNCTION(Vertex3bvOES);
    GLFL_LOAD_FUNCTION(Vertex4bOES);
    GLFL_LOAD_FUNCTION(Vertex4bvOES);
}
void glfl::load_extension_GL_OES_compressed_ETC1_RGB8_sub_texture() {}
void glfl::load_extension_GL_OES_compressed_ETC1_RGB8_texture() {}
void glfl::load_extension_GL_OES_compressed_paletted_texture() {}
void glfl::load_extension_GL_OES_copy_image()
{
    GLFL_LOAD_FUNCTION(CopyImageSubDataOES);
}
void glfl::load_extension_GL_OES_depth24() {}
void glfl::load_extension_GL_OES_depth32() {}
void glfl::load_extension_GL_OES_depth_texture() {}
void glfl::load_extension_GL_OES_draw_buffers_indexed()
{
    GLFL_LOAD_FUNCTION(EnableiOES);
    GLFL_LOAD_FUNCTION(DisableiOES);
    GLFL_LOAD_FUNCTION(BlendEquationiOES);
    GLFL_LOAD_FUNCTION(BlendEquationSeparateiOES);
    GLFL_LOAD_FUNCTION(BlendFunciOES);
    GLFL_LOAD_FUNCTION(BlendFuncSeparateiOES);
    GLFL_LOAD_FUNCTION(ColorMaskiOES);
    GLFL_LOAD_FUNCTION(IsEnablediOES);
}
void glfl::load_extension_GL_OES_draw_elements_base_vertex()
{
    GLFL_LOAD_FUNCTION(DrawElementsBaseVertexOES);
    GLFL_LOAD_FUNCTION(DrawRangeElementsBaseVertexOES);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertexOES);
    GLFL_LOAD_FUNCTION(MultiDrawElementsBaseVertexOES);
}
void glfl::load_extension_GL_OES_draw_texture()
{
    GLFL_LOAD_FUNCTION(DrawTexsOES);
    GLFL_LOAD_FUNCTION(DrawTexiOES);
    GLFL_LOAD_FUNCTION(DrawTexxOES);
    GLFL_LOAD_FUNCTION(DrawTexsvOES);
    GLFL_LOAD_FUNCTION(DrawTexivOES);
    GLFL_LOAD_FUNCTION(DrawTexxvOES);
    GLFL_LOAD_FUNCTION(DrawTexfOES);
    GLFL_LOAD_FUNCTION(DrawTexfvOES);
}
void glfl::load_extension_GL_OES_element_index_uint() {}
void glfl::load_extension_GL_OES_extended_matrix_palette() {}
void glfl::load_extension_GL_OES_fbo_render_mipmap() {}
void glfl::load_extension_GL_OES_fixed_point()
{
    GLFL_LOAD_FUNCTION(AlphaFuncxOES);
    GLFL_LOAD_FUNCTION(ClearColorxOES);
    GLFL_LOAD_FUNCTION(ClearDepthxOES);
    GLFL_LOAD_FUNCTION(ClipPlanexOES);
    GLFL_LOAD_FUNCTION(Color4xOES);
    GLFL_LOAD_FUNCTION(DepthRangexOES);
    GLFL_LOAD_FUNCTION(FogxOES);
    GLFL_LOAD_FUNCTION(FogxvOES);
    GLFL_LOAD_FUNCTION(FrustumxOES);
    GLFL_LOAD_FUNCTION(GetClipPlanexOES);
    GLFL_LOAD_FUNCTION(GetFixedvOES);
    GLFL_LOAD_FUNCTION(GetTexEnvxvOES);
    GLFL_LOAD_FUNCTION(GetTexParameterxvOES);
    GLFL_LOAD_FUNCTION(LightModelxOES);
    GLFL_LOAD_FUNCTION(LightModelxvOES);
    GLFL_LOAD_FUNCTION(LightxOES);
    GLFL_LOAD_FUNCTION(LightxvOES);
    GLFL_LOAD_FUNCTION(LineWidthxOES);
    GLFL_LOAD_FUNCTION(LoadMatrixxOES);
    GLFL_LOAD_FUNCTION(MaterialxOES);
    GLFL_LOAD_FUNCTION(MaterialxvOES);
    GLFL_LOAD_FUNCTION(MultMatrixxOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord4xOES);
    GLFL_LOAD_FUNCTION(Normal3xOES);
    GLFL_LOAD_FUNCTION(OrthoxOES);
    GLFL_LOAD_FUNCTION(PointParameterxvOES);
    GLFL_LOAD_FUNCTION(PointSizexOES);
    GLFL_LOAD_FUNCTION(PolygonOffsetxOES);
    GLFL_LOAD_FUNCTION(RotatexOES);
    GLFL_LOAD_FUNCTION(ScalexOES);
    GLFL_LOAD_FUNCTION(TexEnvxOES);
    GLFL_LOAD_FUNCTION(TexEnvxvOES);
    GLFL_LOAD_FUNCTION(TexParameterxOES);
    GLFL_LOAD_FUNCTION(TexParameterxvOES);
    GLFL_LOAD_FUNCTION(TranslatexOES);
    GLFL_LOAD_FUNCTION(GetLightxvOES);
    GLFL_LOAD_FUNCTION(GetMaterialxvOES);
    GLFL_LOAD_FUNCTION(PointParameterxOES);
    GLFL_LOAD_FUNCTION(SampleCoveragexOES);
    GLFL_LOAD_FUNCTION(AccumxOES);
    GLFL_LOAD_FUNCTION(BitmapxOES);
    GLFL_LOAD_FUNCTION(BlendColorxOES);
    GLFL_LOAD_FUNCTION(ClearAccumxOES);
    GLFL_LOAD_FUNCTION(Color3xOES);
    GLFL_LOAD_FUNCTION(Color3xvOES);
    GLFL_LOAD_FUNCTION(Color4xvOES);
    GLFL_LOAD_FUNCTION(ConvolutionParameterxOES);
    GLFL_LOAD_FUNCTION(ConvolutionParameterxvOES);
    GLFL_LOAD_FUNCTION(EvalCoord1xOES);
    GLFL_LOAD_FUNCTION(EvalCoord1xvOES);
    GLFL_LOAD_FUNCTION(EvalCoord2xOES);
    GLFL_LOAD_FUNCTION(EvalCoord2xvOES);
    GLFL_LOAD_FUNCTION(FeedbackBufferxOES);
    GLFL_LOAD_FUNCTION(GetConvolutionParameterxvOES);
    GLFL_LOAD_FUNCTION(GetHistogramParameterxvOES);
    GLFL_LOAD_FUNCTION(GetLightxOES);
    GLFL_LOAD_FUNCTION(GetMapxvOES);
    GLFL_LOAD_FUNCTION(GetMaterialxOES);
    GLFL_LOAD_FUNCTION(GetPixelMapxv);
    GLFL_LOAD_FUNCTION(GetTexGenxvOES);
    GLFL_LOAD_FUNCTION(GetTexLevelParameterxvOES);
    GLFL_LOAD_FUNCTION(IndexxOES);
    GLFL_LOAD_FUNCTION(IndexxvOES);
    GLFL_LOAD_FUNCTION(LoadTransposeMatrixxOES);
    GLFL_LOAD_FUNCTION(Map1xOES);
    GLFL_LOAD_FUNCTION(Map2xOES);
    GLFL_LOAD_FUNCTION(MapGrid1xOES);
    GLFL_LOAD_FUNCTION(MapGrid2xOES);
    GLFL_LOAD_FUNCTION(MultTransposeMatrixxOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord1xOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord1xvOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord2xOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord2xvOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord3xOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord3xvOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord4xvOES);
    GLFL_LOAD_FUNCTION(Normal3xvOES);
    GLFL_LOAD_FUNCTION(PassThroughxOES);
    GLFL_LOAD_FUNCTION(PixelMapx);
    GLFL_LOAD_FUNCTION(PixelStorex);
    GLFL_LOAD_FUNCTION(PixelTransferxOES);
    GLFL_LOAD_FUNCTION(PixelZoomxOES);
    GLFL_LOAD_FUNCTION(PrioritizeTexturesxOES);
    GLFL_LOAD_FUNCTION(RasterPos2xOES);
    GLFL_LOAD_FUNCTION(RasterPos2xvOES);
    GLFL_LOAD_FUNCTION(RasterPos3xOES);
    GLFL_LOAD_FUNCTION(RasterPos3xvOES);
    GLFL_LOAD_FUNCTION(RasterPos4xOES);
    GLFL_LOAD_FUNCTION(RasterPos4xvOES);
    GLFL_LOAD_FUNCTION(RectxOES);
    GLFL_LOAD_FUNCTION(RectxvOES);
    GLFL_LOAD_FUNCTION(TexCoord1xOES);
    GLFL_LOAD_FUNCTION(TexCoord1xvOES);
    GLFL_LOAD_FUNCTION(TexCoord2xOES);
    GLFL_LOAD_FUNCTION(TexCoord2xvOES);
    GLFL_LOAD_FUNCTION(TexCoord3xOES);
    GLFL_LOAD_FUNCTION(TexCoord3xvOES);
    GLFL_LOAD_FUNCTION(TexCoord4xOES);
    GLFL_LOAD_FUNCTION(TexCoord4xvOES);
    GLFL_LOAD_FUNCTION(TexGenxOES);
    GLFL_LOAD_FUNCTION(TexGenxvOES);
    GLFL_LOAD_FUNCTION(Vertex2xOES);
    GLFL_LOAD_FUNCTION(Vertex2xvOES);
    GLFL_LOAD_FUNCTION(Vertex3xOES);
    GLFL_LOAD_FUNCTION(Vertex3xvOES);
    GLFL_LOAD_FUNCTION(Vertex4xOES);
    GLFL_LOAD_FUNCTION(Vertex4xvOES);
}
void glfl::load_extension_GL_OES_fragment_precision_high() {}
void glfl::load_extension_GL_OES_framebuffer_object()
{
    GLFL_LOAD_FUNCTION(IsRenderbufferOES);
    GLFL_LOAD_FUNCTION(BindRenderbufferOES);
    GLFL_LOAD_FUNCTION(DeleteRenderbuffersOES);
    GLFL_LOAD_FUNCTION(GenRenderbuffersOES);
    GLFL_LOAD_FUNCTION(RenderbufferStorageOES);
    GLFL_LOAD_FUNCTION(GetRenderbufferParameterivOES);
    GLFL_LOAD_FUNCTION(IsFramebufferOES);
    GLFL_LOAD_FUNCTION(BindFramebufferOES);
    GLFL_LOAD_FUNCTION(DeleteFramebuffersOES);
    GLFL_LOAD_FUNCTION(GenFramebuffersOES);
    GLFL_LOAD_FUNCTION(CheckFramebufferStatusOES);
    GLFL_LOAD_FUNCTION(FramebufferRenderbufferOES);
    GLFL_LOAD_FUNCTION(FramebufferTexture2DOES);
    GLFL_LOAD_FUNCTION(GetFramebufferAttachmentParameterivOES);
    GLFL_LOAD_FUNCTION(GenerateMipmapOES);
}
void glfl::load_extension_GL_OES_geometry_point_size() {}
void glfl::load_extension_GL_OES_geometry_shader()
{
    GLFL_LOAD_FUNCTION(FramebufferTextureOES);
}
void glfl::load_extension_GL_OES_get_program_binary()
{
    GLFL_LOAD_FUNCTION(GetProgramBinaryOES);
    GLFL_LOAD_FUNCTION(ProgramBinaryOES);
}
void glfl::load_extension_GL_OES_gpu_shader5() {}
void glfl::load_extension_GL_OES_mapbuffer()
{
    GLFL_LOAD_FUNCTION(MapBufferOES);
    GLFL_LOAD_FUNCTION(UnmapBufferOES);
    GLFL_LOAD_FUNCTION(GetBufferPointervOES);
}
void glfl::load_extension_GL_OES_matrix_get() {}
void glfl::load_extension_GL_OES_matrix_palette()
{
    GLFL_LOAD_FUNCTION(CurrentPaletteMatrixOES);
    GLFL_LOAD_FUNCTION(LoadPaletteFromModelViewMatrixOES);
    GLFL_LOAD_FUNCTION(MatrixIndexPointerOES);
    GLFL_LOAD_FUNCTION(WeightPointerOES);
}
void glfl::load_extension_GL_OES_packed_depth_stencil() {}
void glfl::load_extension_GL_OES_point_size_array()
{
    GLFL_LOAD_FUNCTION(PointSizePointerOES);
}
void glfl::load_extension_GL_OES_point_sprite() {}
void glfl::load_extension_GL_OES_primitive_bounding_box()
{
    GLFL_LOAD_FUNCTION(PrimitiveBoundingBoxOES);
}
void glfl::load_extension_GL_OES_query_matrix()
{
    GLFL_LOAD_FUNCTION(QueryMatrixxOES);
}
void glfl::load_extension_GL_OES_read_format() {}
void glfl::load_extension_GL_OES_required_internalformat() {}
void glfl::load_extension_GL_OES_rgb8_rgba8() {}
void glfl::load_extension_GL_OES_sample_shading()
{
    GLFL_LOAD_FUNCTION(MinSampleShadingOES);
}
void glfl::load_extension_GL_OES_sample_variables() {}
void glfl::load_extension_GL_OES_shader_image_atomic() {}
void glfl::load_extension_GL_OES_shader_io_blocks() {}
void glfl::load_extension_GL_OES_shader_multisample_interpolation() {}
void glfl::load_extension_GL_OES_single_precision()
{
    GLFL_LOAD_FUNCTION(ClearDepthfOES);
    GLFL_LOAD_FUNCTION(ClipPlanefOES);
    GLFL_LOAD_FUNCTION(DepthRangefOES);
    GLFL_LOAD_FUNCTION(FrustumfOES);
    GLFL_LOAD_FUNCTION(GetClipPlanefOES);
    GLFL_LOAD_FUNCTION(OrthofOES);
}
void glfl::load_extension_GL_OES_standard_derivatives() {}
void glfl::load_extension_GL_OES_stencil1() {}
void glfl::load_extension_GL_OES_stencil4() {}
void glfl::load_extension_GL_OES_stencil8() {}
void glfl::load_extension_GL_OES_stencil_wrap() {}
void glfl::load_extension_GL_OES_surfaceless_context() {}
void glfl::load_extension_GL_OES_tessellation_point_size() {}
void glfl::load_extension_GL_OES_tessellation_shader()
{
    GLFL_LOAD_FUNCTION(PatchParameteriOES);
}
void glfl::load_extension_GL_OES_texture_3D()
{
    GLFL_LOAD_FUNCTION(TexImage3DOES);
    GLFL_LOAD_FUNCTION(TexSubImage3DOES);
    GLFL_LOAD_FUNCTION(CopyTexSubImage3DOES);
    GLFL_LOAD_FUNCTION(CompressedTexImage3DOES);
    GLFL_LOAD_FUNCTION(CompressedTexSubImage3DOES);
    GLFL_LOAD_FUNCTION(FramebufferTexture3DOES);
}
void glfl::load_extension_GL_OES_texture_border_clamp()
{
    GLFL_LOAD_FUNCTION(TexParameterIivOES);
    GLFL_LOAD_FUNCTION(TexParameterIuivOES);
    GLFL_LOAD_FUNCTION(GetTexParameterIivOES);
    GLFL_LOAD_FUNCTION(GetTexParameterIuivOES);
    GLFL_LOAD_FUNCTION(SamplerParameterIivOES);
    GLFL_LOAD_FUNCTION(SamplerParameterIuivOES);
    GLFL_LOAD_FUNCTION(GetSamplerParameterIivOES);
    GLFL_LOAD_FUNCTION(GetSamplerParameterIuivOES);
}
void glfl::load_extension_GL_OES_texture_buffer()
{
    GLFL_LOAD_FUNCTION(TexBufferOES);
    GLFL_LOAD_FUNCTION(TexBufferRangeOES);
}
void glfl::load_extension_GL_OES_texture_compression_astc() {}
void glfl::load_extension_GL_OES_texture_cube_map()
{
    GLFL_LOAD_FUNCTION(TexGenfOES);
    GLFL_LOAD_FUNCTION(TexGenfvOES);
    GLFL_LOAD_FUNCTION(TexGeniOES);
    GLFL_LOAD_FUNCTION(TexGenivOES);
    GLFL_LOAD_FUNCTION(TexGenxOES);
    GLFL_LOAD_FUNCTION(TexGenxvOES);
    GLFL_LOAD_FUNCTION(GetTexGenfvOES);
    GLFL_LOAD_FUNCTION(GetTexGenivOES);
    GLFL_LOAD_FUNCTION(GetTexGenxvOES);
}
void glfl::load_extension_GL_OES_texture_cube_map_array() {}
void glfl::load_extension_GL_OES_texture_env_crossbar() {}
void glfl::load_extension_GL_OES_texture_float() {}
void glfl::load_extension_GL_OES_texture_float_linear() {}
void glfl::load_extension_GL_OES_texture_half_float() {}
void glfl::load_extension_GL_OES_texture_half_float_linear() {}
void glfl::load_extension_GL_OES_texture_mirrored_repeat() {}
void glfl::load_extension_GL_OES_texture_npot() {}
void glfl::load_extension_GL_OES_texture_stencil8() {}
void glfl::load_extension_GL_OES_texture_storage_multisample_2d_array()
{
    GLFL_LOAD_FUNCTION(TexStorage3DMultisampleOES);
}
void glfl::load_extension_GL_OES_texture_view()
{
    GLFL_LOAD_FUNCTION(TextureViewOES);
}
void glfl::load_extension_GL_OES_vertex_array_object()
{
    GLFL_LOAD_FUNCTION(BindVertexArrayOES);
    GLFL_LOAD_FUNCTION(DeleteVertexArraysOES);
    GLFL_LOAD_FUNCTION(GenVertexArraysOES);
    GLFL_LOAD_FUNCTION(IsVertexArrayOES);
}
void glfl::load_extension_GL_OES_vertex_half_float() {}
void glfl::load_extension_GL_OES_vertex_type_10_10_10_2() {}
void glfl::load_extension_GL_OES_viewport_array()
{
    GLFL_LOAD_FUNCTION(ViewportArrayvOES);
    GLFL_LOAD_FUNCTION(ViewportIndexedfOES);
    GLFL_LOAD_FUNCTION(ViewportIndexedfvOES);
    GLFL_LOAD_FUNCTION(ScissorArrayvOES);
    GLFL_LOAD_FUNCTION(ScissorIndexedOES);
    GLFL_LOAD_FUNCTION(ScissorIndexedvOES);
    GLFL_LOAD_FUNCTION(DepthRangeArrayfvOES);
    GLFL_LOAD_FUNCTION(DepthRangeIndexedfOES);
    GLFL_LOAD_FUNCTION(GetFloati_vOES);
    GLFL_LOAD_FUNCTION(EnableiOES);
    GLFL_LOAD_FUNCTION(DisableiOES);
    GLFL_LOAD_FUNCTION(IsEnablediOES);
}
void glfl::load_extension_GL_OML_interlace() {}
void glfl::load_extension_GL_OML_resample() {}
void glfl::load_extension_GL_OML_subsample() {}
void glfl::load_extension_GL_OVR_multiview()
{
    GLFL_LOAD_FUNCTION(FramebufferTextureMultiviewOVR);
}
void glfl::load_extension_GL_OVR_multiview2() {}
void glfl::load_extension_GL_OVR_multiview_multisampled_render_to_texture()
{
    GLFL_LOAD_FUNCTION(FramebufferTextureMultisampleMultiviewOVR);
}
void glfl::load_extension_GL_PGI_misc_hints()
{
    GLFL_LOAD_FUNCTION(HintPGI);
}
void glfl::load_extension_GL_PGI_vertex_hints() {}
void glfl::load_extension_GL_QCOM_alpha_test()
{
    GLFL_LOAD_FUNCTION(AlphaFuncQCOM);
}
void glfl::load_extension_GL_QCOM_binning_control() {}
void glfl::load_extension_GL_QCOM_driver_control()
{
    GLFL_LOAD_FUNCTION(GetDriverControlsQCOM);
    GLFL_LOAD_FUNCTION(GetDriverControlStringQCOM);
    GLFL_LOAD_FUNCTION(EnableDriverControlQCOM);
    GLFL_LOAD_FUNCTION(DisableDriverControlQCOM);
}
void glfl::load_extension_GL_QCOM_extended_get()
{
    GLFL_LOAD_FUNCTION(ExtGetTexturesQCOM);
    GLFL_LOAD_FUNCTION(ExtGetBuffersQCOM);
    GLFL_LOAD_FUNCTION(ExtGetRenderbuffersQCOM);
    GLFL_LOAD_FUNCTION(ExtGetFramebuffersQCOM);
    GLFL_LOAD_FUNCTION(ExtGetTexLevelParameterivQCOM);
    GLFL_LOAD_FUNCTION(ExtTexObjectStateOverrideiQCOM);
    GLFL_LOAD_FUNCTION(ExtGetTexSubImageQCOM);
    GLFL_LOAD_FUNCTION(ExtGetBufferPointervQCOM);
}
void glfl::load_extension_GL_QCOM_extended_get2()
{
    GLFL_LOAD_FUNCTION(ExtGetShadersQCOM);
    GLFL_LOAD_FUNCTION(ExtGetProgramsQCOM);
    GLFL_LOAD_FUNCTION(ExtIsProgramBinaryQCOM);
    GLFL_LOAD_FUNCTION(ExtGetProgramBinarySourceQCOM);
}
void glfl::load_extension_GL_QCOM_perfmon_global_mode() {}
void glfl::load_extension_GL_QCOM_tiled_rendering()
{
    GLFL_LOAD_FUNCTION(StartTilingQCOM);
    GLFL_LOAD_FUNCTION(EndTilingQCOM);
}
void glfl::load_extension_GL_QCOM_writeonly_rendering() {}
void glfl::load_extension_GL_REND_screen_coordinates() {}
void glfl::load_extension_GL_S3_s3tc() {}
void glfl::load_extension_GL_SGIS_detail_texture()
{
    GLFL_LOAD_FUNCTION(DetailTexFuncSGIS);
    GLFL_LOAD_FUNCTION(GetDetailTexFuncSGIS);
}
void glfl::load_extension_GL_SGIS_fog_function()
{
    GLFL_LOAD_FUNCTION(FogFuncSGIS);
    GLFL_LOAD_FUNCTION(GetFogFuncSGIS);
}
void glfl::load_extension_GL_SGIS_generate_mipmap() {}
void glfl::load_extension_GL_SGIS_multisample()
{
    GLFL_LOAD_FUNCTION(SampleMaskSGIS);
    GLFL_LOAD_FUNCTION(SamplePatternSGIS);
}
void glfl::load_extension_GL_SGIS_pixel_texture()
{
    GLFL_LOAD_FUNCTION(PixelTexGenParameteriSGIS);
    GLFL_LOAD_FUNCTION(PixelTexGenParameterivSGIS);
    GLFL_LOAD_FUNCTION(PixelTexGenParameterfSGIS);
    GLFL_LOAD_FUNCTION(PixelTexGenParameterfvSGIS);
    GLFL_LOAD_FUNCTION(GetPixelTexGenParameterivSGIS);
    GLFL_LOAD_FUNCTION(GetPixelTexGenParameterfvSGIS);
}
void glfl::load_extension_GL_SGIS_point_line_texgen() {}
void glfl::load_extension_GL_SGIS_point_parameters()
{
    GLFL_LOAD_FUNCTION(PointParameterfSGIS);
    GLFL_LOAD_FUNCTION(PointParameterfvSGIS);
}
void glfl::load_extension_GL_SGIS_sharpen_texture()
{
    GLFL_LOAD_FUNCTION(SharpenTexFuncSGIS);
    GLFL_LOAD_FUNCTION(GetSharpenTexFuncSGIS);
}
void glfl::load_extension_GL_SGIS_texture4D()
{
    GLFL_LOAD_FUNCTION(TexImage4DSGIS);
    GLFL_LOAD_FUNCTION(TexSubImage4DSGIS);
}
void glfl::load_extension_GL_SGIS_texture_border_clamp() {}
void glfl::load_extension_GL_SGIS_texture_color_mask()
{
    GLFL_LOAD_FUNCTION(TextureColorMaskSGIS);
}
void glfl::load_extension_GL_SGIS_texture_edge_clamp() {}
void glfl::load_extension_GL_SGIS_texture_filter4()
{
    GLFL_LOAD_FUNCTION(GetTexFilterFuncSGIS);
    GLFL_LOAD_FUNCTION(TexFilterFuncSGIS);
}
void glfl::load_extension_GL_SGIS_texture_lod() {}
void glfl::load_extension_GL_SGIS_texture_select() {}
void glfl::load_extension_GL_SGIX_async()
{
    GLFL_LOAD_FUNCTION(AsyncMarkerSGIX);
    GLFL_LOAD_FUNCTION(FinishAsyncSGIX);
    GLFL_LOAD_FUNCTION(PollAsyncSGIX);
    GLFL_LOAD_FUNCTION(GenAsyncMarkersSGIX);
    GLFL_LOAD_FUNCTION(DeleteAsyncMarkersSGIX);
    GLFL_LOAD_FUNCTION(IsAsyncMarkerSGIX);
}
void glfl::load_extension_GL_SGIX_async_histogram() {}
void glfl::load_extension_GL_SGIX_async_pixel() {}
void glfl::load_extension_GL_SGIX_blend_alpha_minmax() {}
void glfl::load_extension_GL_SGIX_calligraphic_fragment() {}
void glfl::load_extension_GL_SGIX_clipmap() {}
void glfl::load_extension_GL_SGIX_convolution_accuracy() {}
void glfl::load_extension_GL_SGIX_depth_pass_instrument() {}
void glfl::load_extension_GL_SGIX_depth_texture() {}
void glfl::load_extension_GL_SGIX_flush_raster()
{
    GLFL_LOAD_FUNCTION(FlushRasterSGIX);
}
void glfl::load_extension_GL_SGIX_fog_offset() {}
void glfl::load_extension_GL_SGIX_fragment_lighting()
{
    GLFL_LOAD_FUNCTION(FragmentColorMaterialSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightfSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightfvSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightiSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightivSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightModelfSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightModelfvSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightModeliSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightModelivSGIX);
    GLFL_LOAD_FUNCTION(FragmentMaterialfSGIX);
    GLFL_LOAD_FUNCTION(FragmentMaterialfvSGIX);
    GLFL_LOAD_FUNCTION(FragmentMaterialiSGIX);
    GLFL_LOAD_FUNCTION(FragmentMaterialivSGIX);
    GLFL_LOAD_FUNCTION(GetFragmentLightfvSGIX);
    GLFL_LOAD_FUNCTION(GetFragmentLightivSGIX);
    GLFL_LOAD_FUNCTION(GetFragmentMaterialfvSGIX);
    GLFL_LOAD_FUNCTION(GetFragmentMaterialivSGIX);
    GLFL_LOAD_FUNCTION(LightEnviSGIX);
}
void glfl::load_extension_GL_SGIX_framezoom()
{
    GLFL_LOAD_FUNCTION(FrameZoomSGIX);
}
void glfl::load_extension_GL_SGIX_igloo_interface()
{
    GLFL_LOAD_FUNCTION(IglooInterfaceSGIX);
}
void glfl::load_extension_GL_SGIX_instruments()
{
    GLFL_LOAD_FUNCTION(GetInstrumentsSGIX);
    GLFL_LOAD_FUNCTION(InstrumentsBufferSGIX);
    GLFL_LOAD_FUNCTION(PollInstrumentsSGIX);
    GLFL_LOAD_FUNCTION(ReadInstrumentsSGIX);
    GLFL_LOAD_FUNCTION(StartInstrumentsSGIX);
    GLFL_LOAD_FUNCTION(StopInstrumentsSGIX);
}
void glfl::load_extension_GL_SGIX_interlace() {}
void glfl::load_extension_GL_SGIX_ir_instrument1() {}
void glfl::load_extension_GL_SGIX_list_priority()
{
    GLFL_LOAD_FUNCTION(GetListParameterfvSGIX);
    GLFL_LOAD_FUNCTION(GetListParameterivSGIX);
    GLFL_LOAD_FUNCTION(ListParameterfSGIX);
    GLFL_LOAD_FUNCTION(ListParameterfvSGIX);
    GLFL_LOAD_FUNCTION(ListParameteriSGIX);
    GLFL_LOAD_FUNCTION(ListParameterivSGIX);
}
void glfl::load_extension_GL_SGIX_pixel_texture()
{
    GLFL_LOAD_FUNCTION(PixelTexGenSGIX);
}
void glfl::load_extension_GL_SGIX_pixel_tiles() {}
void glfl::load_extension_GL_SGIX_polynomial_ffd()
{
    GLFL_LOAD_FUNCTION(DeformationMap3dSGIX);
    GLFL_LOAD_FUNCTION(DeformationMap3fSGIX);
    GLFL_LOAD_FUNCTION(DeformSGIX);
    GLFL_LOAD_FUNCTION(LoadIdentityDeformationMapSGIX);
}
void glfl::load_extension_GL_SGIX_reference_plane()
{
    GLFL_LOAD_FUNCTION(ReferencePlaneSGIX);
}
void glfl::load_extension_GL_SGIX_resample() {}
void glfl::load_extension_GL_SGIX_scalebias_hint() {}
void glfl::load_extension_GL_SGIX_shadow() {}
void glfl::load_extension_GL_SGIX_shadow_ambient() {}
void glfl::load_extension_GL_SGIX_sprite()
{
    GLFL_LOAD_FUNCTION(SpriteParameterfSGIX);
    GLFL_LOAD_FUNCTION(SpriteParameterfvSGIX);
    GLFL_LOAD_FUNCTION(SpriteParameteriSGIX);
    GLFL_LOAD_FUNCTION(SpriteParameterivSGIX);
}
void glfl::load_extension_GL_SGIX_subsample() {}
void glfl::load_extension_GL_SGIX_tag_sample_buffer()
{
    GLFL_LOAD_FUNCTION(TagSampleBufferSGIX);
}
void glfl::load_extension_GL_SGIX_texture_add_env() {}
void glfl::load_extension_GL_SGIX_texture_coordinate_clamp() {}
void glfl::load_extension_GL_SGIX_texture_lod_bias() {}
void glfl::load_extension_GL_SGIX_texture_multi_buffer() {}
void glfl::load_extension_GL_SGIX_texture_scale_bias() {}
void glfl::load_extension_GL_SGIX_vertex_preclip() {}
void glfl::load_extension_GL_SGIX_ycrcb() {}
void glfl::load_extension_GL_SGIX_ycrcb_subsample() {}
void glfl::load_extension_GL_SGIX_ycrcba() {}
void glfl::load_extension_GL_SGI_color_matrix() {}
void glfl::load_extension_GL_SGI_color_table()
{
    GLFL_LOAD_FUNCTION(ColorTableSGI);
    GLFL_LOAD_FUNCTION(ColorTableParameterfvSGI);
    GLFL_LOAD_FUNCTION(ColorTableParameterivSGI);
    GLFL_LOAD_FUNCTION(CopyColorTableSGI);
    GLFL_LOAD_FUNCTION(GetColorTableSGI);
    GLFL_LOAD_FUNCTION(GetColorTableParameterfvSGI);
    GLFL_LOAD_FUNCTION(GetColorTableParameterivSGI);
}
void glfl::load_extension_GL_SGI_texture_color_table() {}
void glfl::load_extension_GL_SUNX_constant_data()
{
    GLFL_LOAD_FUNCTION(FinishTextureSUNX);
}
void glfl::load_extension_GL_SUN_convolution_border_modes() {}
void glfl::load_extension_GL_SUN_global_alpha()
{
    GLFL_LOAD_FUNCTION(GlobalAlphaFactorbSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactorsSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactoriSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactorfSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactordSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactorubSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactorusSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactoruiSUN);
}
void glfl::load_extension_GL_SUN_mesh_array()
{
    GLFL_LOAD_FUNCTION(DrawMeshArraysSUN);
}
void glfl::load_extension_GL_SUN_slice_accum() {}
void glfl::load_extension_GL_SUN_triangle_list()
{
    GLFL_LOAD_FUNCTION(ReplacementCodeuiSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeusSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeubSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuivSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeusvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeubvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodePointerSUN);
}
void glfl::load_extension_GL_SUN_vertex()
{
    GLFL_LOAD_FUNCTION(Color4ubVertex2fSUN);
    GLFL_LOAD_FUNCTION(Color4ubVertex2fvSUN);
    GLFL_LOAD_FUNCTION(Color4ubVertex3fSUN);
    GLFL_LOAD_FUNCTION(Color4ubVertex3fvSUN);
    GLFL_LOAD_FUNCTION(Color3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(Color3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(Normal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(Normal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(Color4fNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(Color4fNormal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fVertex3fSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord4fVertex4fSUN);
    GLFL_LOAD_FUNCTION(TexCoord4fVertex4fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fColor4ubVertex3fSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fColor4ubVertex3fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fColor3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fColor3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fNormal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fColor4fNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fColor4fNormal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord4fColor4fNormal3fVertex4fSUN);
    GLFL_LOAD_FUNCTION(TexCoord4fColor4fNormal3fVertex4fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiColor4ubVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiColor4ubVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiColor3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiColor3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiNormal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiColor4fNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiColor4fNormal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiTexCoord2fVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiTexCoord2fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiTexCoord2fNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN);
}
void glfl::load_extension_GL_VIV_shader_binary() {}
void glfl::load_extension_GL_WIN_phong_shading() {}
void glfl::load_extension_GL_WIN_specular_fog() {}

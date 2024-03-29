
/*
 * public xen defines and struct for x86_32
 * generated by mkheader.py -- DO NOT EDIT
 */

#ifndef __FOREIGN_X86_32_H_TMP__
#define __FOREIGN_X86_32_H_TMP__ 1


#define __DECL_REG_LO8(which) uint32_t e ## which ## x
#define __DECL_REG_LO16(name) uint32_t e ## name
#define __i386___X86_32 1
#pragma pack(4)

#define FLAT_RING1_CS_X86_32 0xe019    /* GDT index 259 */
#define FLAT_RING1_DS_X86_32 0xe021    /* GDT index 260 */
#define FLAT_RING1_SS_X86_32 0xe021    /* GDT index 260 */
#define FLAT_KERNEL_CS_X86_32 FLAT_RING1_CS_X86_32
#define FLAT_KERNEL_DS_X86_32 FLAT_RING1_DS_X86_32
#define FLAT_KERNEL_SS_X86_32 FLAT_RING1_SS_X86_32
#define xen_pfn_to_cr3_x86_32(pfn) (((unsigned)(pfn) << 12) | ((unsigned)(pfn) >> 20))
#define xen_cr3_to_pfn_x86_32(cr3) (((unsigned)(cr3) >> 12) | ((unsigned)(cr3) << 20))
#define XEN_HAVE_PV_GUEST_ENTRY_X86_32 1
#define XEN_LEGACY_MAX_VCPUS_X86_32 32
#define _VGCF_i387_valid_X86_32               0
#define VGCF_i387_valid_X86_32                (1<<_VGCF_i387_valid_X86_32)
#define _VGCF_in_kernel_X86_32                2
#define VGCF_in_kernel_X86_32                 (1<<_VGCF_in_kernel_X86_32)
#define _VGCF_failsafe_disables_events_X86_32 3
#define VGCF_failsafe_disables_events_X86_32  (1<<_VGCF_failsafe_disables_events_X86_32)
#define _VGCF_syscall_disables_events_X86_32  4
#define VGCF_syscall_disables_events_X86_32   (1<<_VGCF_syscall_disables_events_X86_32)
#define _VGCF_online_X86_32                   5
#define VGCF_online_X86_32                    (1<<_VGCF_online_X86_32)
#define MAX_GUEST_CMDLINE_X86_32 1024

#define x86_32_has_no_vcpu_cr_regs 1

#define x86_32_has_no_vcpu_ar_regs 1

struct start_info_x86_32 {
    char magic[32];             
    uint32_t nr_pages;     
    uint32_t shared_info;  
    uint32_t flags;             
    uint32_t store_mfn;        
    uint32_t store_evtchn;      
    union {
        struct {
            uint32_t mfn;      
            uint32_t  evtchn;   
        } domU;
        struct {
            uint32_t info_off;  
            uint32_t info_size; 
        } dom0;
    } console;
    uint32_t pt_base;      
    uint32_t nr_pt_frames; 
    uint32_t mfn_list;     
    uint32_t mod_start;    
    uint32_t mod_len;      
    int8_t cmd_line[MAX_GUEST_CMDLINE_X86_32];
    uint32_t first_p2m_pfn;
    uint32_t nr_p2m_frames;
};
typedef struct start_info_x86_32 start_info_x86_32_t;

struct trap_info_x86_32 {
    uint8_t       vector;  
    uint8_t       flags;   
    uint16_t      cs;      
    uint32_t address; 
};
typedef struct trap_info_x86_32 trap_info_x86_32_t;

struct cpu_user_regs_x86_32 {
    __DECL_REG_LO8(b);
    __DECL_REG_LO8(c);
    __DECL_REG_LO8(d);
    __DECL_REG_LO16(si);
    __DECL_REG_LO16(di);
    __DECL_REG_LO16(bp);
    __DECL_REG_LO8(a);
    uint16_t error_code;    
    uint16_t entry_vector;  
    __DECL_REG_LO16(ip);
    uint16_t cs;
    uint8_t  saved_upcall_mask;
    uint8_t  _pad0;
    __DECL_REG_LO16(flags); 
    __DECL_REG_LO16(sp);
    uint16_t ss, _pad1;
    uint16_t es, _pad2;
    uint16_t ds, _pad3;
    uint16_t fs, _pad4;
    uint16_t gs, _pad5;
};
typedef struct cpu_user_regs_x86_32 cpu_user_regs_x86_32_t;

#define x86_32_has_no_vcpu_guest_core_regs 1

struct vcpu_guest_context_x86_32 {
    struct { char x[512]; } fpu_ctxt;       
    uint32_t flags;                    
    struct cpu_user_regs_x86_32 user_regs;         
    struct trap_info_x86_32 trap_ctxt[256];        
    uint32_t ldt_base, ldt_ents;       
    uint32_t gdt_frames[16], gdt_ents; 
    uint32_t kernel_ss, kernel_sp;     
    uint32_t ctrlreg[8];               
    uint32_t debugreg[8];              
#ifdef __i386___X86_32
    uint32_t event_callback_cs;        
    uint32_t event_callback_eip;
    uint32_t failsafe_callback_cs;     
    uint32_t failsafe_callback_eip;
#else
    uint32_t event_callback_eip;
    uint32_t failsafe_callback_eip;
#ifdef __XEN__
    union {
        uint32_t syscall_callback_eip;
        struct {
            unsigned int event_callback_cs;    
            unsigned int failsafe_callback_cs; 
        };
    };
#else
    uint32_t syscall_callback_eip;
#endif
#endif
    uint32_t vm_assist;                
#ifdef __x86_64___X86_32
    uint64_t      fs_base;
    uint64_t      gs_base_kernel;
    uint64_t      gs_base_user;
#endif
};
typedef struct vcpu_guest_context_x86_32 vcpu_guest_context_x86_32_t;

struct arch_vcpu_info_x86_32 {
    uint32_t cr2;
    uint32_t pad[5]; 
};
typedef struct arch_vcpu_info_x86_32 arch_vcpu_info_x86_32_t;

struct vcpu_time_info_x86_32 {
    uint32_t version;
    uint32_t pad0;
    uint64_t tsc_timestamp;   
    uint64_t system_time;     
    uint32_t tsc_to_system_mul;
    int8_t   tsc_shift;
#if __XEN_INTERFACE_VERSION__ > 0x040600
    uint8_t  flags;
    uint8_t  pad1[2];
#else
    int8_t   pad1[3];
#endif
};
typedef struct vcpu_time_info_x86_32 vcpu_time_info_x86_32_t;

struct vcpu_info_x86_32 {
    uint8_t evtchn_upcall_pending;
#ifdef XEN_HAVE_PV_UPCALL_MASK
    uint8_t evtchn_upcall_mask;
#else 
    uint8_t pad0;
#endif 
    uint32_t evtchn_pending_sel;
    struct arch_vcpu_info_x86_32 arch;
    struct vcpu_time_info_x86_32 time;
};
typedef struct vcpu_info_x86_32 vcpu_info_x86_32_t;

struct arch_shared_info_x86_32 {
    uint32_t max_pfn;
    uint32_t     pfn_to_mfn_frame_list_list;
    uint32_t nmi_reason;
    uint32_t p2m_cr3;         
    uint32_t p2m_vaddr;       
    uint32_t p2m_generation;  
#ifdef __i386___X86_32
    uint32_t wc_sec_hi;
#endif
};
typedef struct arch_shared_info_x86_32 arch_shared_info_x86_32_t;

struct shared_info_x86_32 {
    struct vcpu_info_x86_32 vcpu_info[XEN_LEGACY_MAX_VCPUS_X86_32];
    uint32_t evtchn_pending[sizeof(uint32_t) * 8];
    uint32_t evtchn_mask[sizeof(uint32_t) * 8];
    uint32_t wc_version;      
    uint32_t wc_sec;          
    uint32_t wc_nsec;         
#if !defined(__i386___X86_32)
    uint32_t wc_sec_hi;
# define xen_wc_sec_hi wc_sec_hi
#elif !defined(__XEN__) && !defined(__XEN_TOOLS__)
# define xen_wc_sec_hi arch.wc_sec_hi
#endif
    struct arch_shared_info_x86_32 arch;
};
typedef struct shared_info_x86_32 shared_info_x86_32_t;


#undef __DECL_REG_LO8
#undef __DECL_REG_LO16
#pragma pack()

#endif /* __FOREIGN_X86_32_H_TMP__ */

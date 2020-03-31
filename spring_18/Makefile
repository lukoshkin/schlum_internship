cxxflags := -std=c++17			 	
gsl_links := -lgsl -lgslcblas -lm

OBJDIR := object_files
EX_OBJ := $(addprefix $(OBJDIR)/, main.o coefficients.o fourier_method.o \
										brents_method.o iteration_function.o)
APPR_OBJ := $(addprefix $(OBJDIR)/, test.o) 

VPATH := numerical analytical



all : approximate_solution exact_solution



exact_solution : $(EX_OBJ)
	g++ -o $@ $(EX_OBJ) $(gsl_links)

$(EX_OBJ) : $(OBJDIR)/%.o : %.cpp
	g++ -c -o $(OBJDIR)/$*.o $<

$(OBJDIR)/main.o : analytical.h 
$(EX_OBJ) : | $(OBJDIR)



approximate_solution : $(APPR_OBJ)
	g++ -o $@ $(APPR_OBJ)

$(APPR_OBJ) : $(OBJDIR)/%.o : %.cpp
	g++ -c -o $(OBJDIR)/$*.o $< $(cxxflags)

$(OBJDIR)/test.o : numerical.h
$(APPR_OBJ) : | $(OBJDIR)



%.h : set_all_params_here
	@rm -f M
	python substitute.py



$(OBJDIR) :
	mkdir $(OBJDIR)


.PHONY : plot 
plot : plot_evolution.py style \
	   edata.tsv adata.tsv 
	python plot_evolution.py > /dev/null 2>&1 

adata.tsv : 
	@echo "$@ is not found. Try something of this:"  
	@echo "  make\n./approximate_solution"	 
	@echo "-----------------------------"
edata.tsv : 
	@echo "$@ is not found. Try something of this:"  
	@echo "  make\n./approximate_solution"	 
	@echo "............................."


output := $(shell ls style 2> /dev/null) 

style : 
	@python create_default_style.py


.PHONY : cleanexec cleanobj cleandata clean-all

clean : cleanexec cleanobj
	rm -f M

clean-all : clean cleandata
	rm -f style.mplstyle

cleanexec :
	rm -f exact_solution approximate_solution

cleanobj : ; rm -rf $(OBJDIR)

cleandata :
	rm -f *.tsv
	rm -rf storage

# -*- coding: utf-8 -*-
#This file contains inventory specific table definitions

db.define_table('category',
			Field('company_id','reference company',required=True),
			Field('name','string',required=True),
			Field('cat_desc','string')
			)

db.define_table('inventory_item_type',
				Field('company_id','reference company',required=True),
				Field('name','string',required=True),
				Field('type_desc','string'),
				)

db.define_table('inventory_item',
				Field('company_id','reference company',required=True),
				Field('cat_id','reference category',required=True),
				Field('name','string',required=True),
				Field('item_desc','string'),
				Field('default_purchase_price','integer',required=True),
				Field('default_selling_price','integer',required=True),
				Field('sku','integer'),
				Field('item_type','reference inventory_item_type',required=True),
				Field('quantity','integer',required=True),
				Field('lowest_inventory_threshold','integer',default=0))